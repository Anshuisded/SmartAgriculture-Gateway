#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "agri_sensor"
#define CLASS_NAME  "agri"

static dev_t device_number;
static struct cdev agri_cdev;
static struct class *agri_class;

static char sensor_data[256] = "soil_moisture=50|temperature=25|humidity=60|battery=90\n";

static int agri_open(struct inode *inode, struct file *file)
{
    pr_info("agri_sensor: device opened\n");
    return 0;
}

static int agri_release(struct inode *inode, struct file *file)
{
    pr_info("agri_sensor: device closed\n");
    return 0;
}

static ssize_t agri_read(
    struct file *file,
    char __user *buffer,
    size_t length,
    loff_t *offset)
{
    size_t data_length = strlen(sensor_data);

    if (*offset >= data_length)
        return 0;

    if (length > data_length - *offset)
        length = data_length - *offset;

    if (copy_to_user(buffer, sensor_data + *offset, length))
        return -EFAULT;

    *offset += length;

    return length;
}

static ssize_t agri_write(
    struct file *file,
    const char __user *buffer,
    size_t length,
    loff_t *offset)
{
    if (length >= sizeof(sensor_data))
        length = sizeof(sensor_data) - 1;

    if (copy_from_user(sensor_data, buffer, length))
        return -EFAULT;

    sensor_data[length] = '\0';

    pr_info("agri_sensor: sensor data updated\n");

    return length;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = agri_open,
    .release = agri_release,
    .read = agri_read,
    .write = agri_write,
};

static int __init agri_init(void)
{
    int result;

    result = alloc_chrdev_region(&device_number, 0, 1, DEVICE_NAME);

    if (result < 0)
        return result;

    cdev_init(&agri_cdev, &fops);

    result = cdev_add(&agri_cdev, device_number, 1);

    if (result < 0) {
        unregister_chrdev_region(device_number, 1);
        return result;
    }

    agri_class = class_create(CLASS_NAME);

    if (IS_ERR(agri_class)) {
        cdev_del(&agri_cdev);
        unregister_chrdev_region(device_number, 1);
        return PTR_ERR(agri_class);
    }

    if (IS_ERR(device_create(
            agri_class,
            NULL,
            device_number,
            NULL,
            DEVICE_NAME))) {

        class_destroy(agri_class);
        cdev_del(&agri_cdev);
        unregister_chrdev_region(device_number, 1);

        return -1;
    }

    pr_info("agri_sensor: driver loaded\n");

    return 0;
}

static void __exit agri_exit(void)
{
    device_destroy(agri_class, device_number);
    class_destroy(agri_class);
    cdev_del(&agri_cdev);
    unregister_chrdev_region(device_number, 1);

    pr_info("agri_sensor: driver unloaded\n");
}

module_init(agri_init);
module_exit(agri_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anshuman Mohapatra");
MODULE_DESCRIPTION("Smart Agriculture Soil Moisture Character Device Driver");
MODULE_VERSION("1.0");
