#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd;
    char buffer[256] = {0};
    const char *data = "soil_moisture=42.5";

    fd = open("/dev/agri_sensor", O_RDWR);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (write(fd, data, strlen(data)) < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Data written to driver: %s\n", data);

    lseek(fd, 0, SEEK_SET);

    if (read(fd, buffer, sizeof(buffer) - 1) < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Data read from driver: %s\n", buffer);

    close(fd);
    return 0;
}
