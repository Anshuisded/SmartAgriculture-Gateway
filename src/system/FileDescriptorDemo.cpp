#include "system/FileDescriptorDemo.h"

#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>

void FileDescriptorDemo::runTest() {

    const char* fileName = "logs/fd_test.log";
    const char* message = "Telemetry data written using Linux file descriptors.\n";

    int fd = open(fileName, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1) {
        std::cerr << "Failed to open file: "
                  << std::strerror(errno) << std::endl;
        return;
    }

    std::cout << "File opened successfully. FD = " << fd << std::endl;

    ssize_t bytesWritten =
        write(fd, message, std::strlen(message));

    if (bytesWritten == -1) {
        std::cerr << "Write failed: "
                  << std::strerror(errno) << std::endl;
        close(fd);
        return;
    }

    std::cout << "Bytes written: " << bytesWritten << std::endl;

    close(fd);

    fd = open(fileName, O_RDONLY);

    if (fd == -1) {
        std::cerr << "Failed to reopen file." << std::endl;
        return;
    }

    char buffer[256] = {0};

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);

    if (bytesRead == -1) {
        std::cerr << "Read failed: "
                  << std::strerror(errno) << std::endl;
        close(fd);
        return;
    }

    buffer[bytesRead] = '\0';

    std::cout << "Bytes read: " << bytesRead << std::endl;
    std::cout << "Data read: " << buffer;

    close(fd);

    std::cout << "File descriptor test completed." << std::endl;
}
