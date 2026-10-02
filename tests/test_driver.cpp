#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

int main() {
    const char* device = "/dev/agri_sensor";

    // Open device for initial read
    int fd = open(device, O_RDWR);

    if (fd < 0) {
        std::cerr << "FAIL: Could not open " << device << "\n";
        return 1;
    }

    std::cout << "PASS: Device opened successfully.\n";

    char buffer[256] = {0};

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);

    if (bytesRead < 0) {
        std::cerr << "FAIL: Could not read from device.\n";
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0';

    std::cout << "Initial sensor data:\n";
    std::cout << buffer << "\n";

    // Write new sensor data
    const std::string newData =
        "soil_moisture=35|temperature=28|humidity=65|battery=85";

    ssize_t bytesWritten =
        write(fd, newData.c_str(), newData.size());

    if (bytesWritten < 0) {
        std::cerr << "FAIL: Could not write to device.\n";
        close(fd);
        return 1;
    }

    std::cout << "PASS: Sensor data written successfully.\n";

    close(fd);

    // Reopen device and verify updated data
    fd = open(device, O_RDONLY);

    if (fd < 0) {
        std::cerr << "FAIL: Could not reopen device.\n";
        return 1;
    }

    std::cout << "PASS: Device reopened successfully.\n";

    std::memset(buffer, 0, sizeof(buffer));

    bytesRead = read(fd, buffer, sizeof(buffer) - 1);

    if (bytesRead < 0) {
        std::cerr << "FAIL: Could not read updated data.\n";
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0';

    std::cout << "Updated sensor data:\n";
    std::cout << buffer << "\n";

    const std::string expected =
        "soil_moisture=35|temperature=28|humidity=65|battery=85";

    if (std::string(buffer) != expected) {
        std::cerr << "FAIL: Updated sensor data does not match expected data.\n";
        close(fd);
        return 1;
    }

    std::cout << "PASS: Updated sensor data verified successfully.\n";

    close(fd);

    std::cout << "PASS: Device closed successfully.\n";
    std::cout << "Driver test completed successfully.\n";

    return 0;
}
