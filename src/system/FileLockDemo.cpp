#include "system/FileLockDemo.h"

#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>

void FileLockDemo::runTest() {

    const char* fileName = "logs/file_lock_test.log";

    int fd = open(
        fileName,
        O_CREAT | O_RDWR | O_TRUNC,
        0644
    );

    if (fd == -1) {
        std::cerr << "Failed to open file: "
                  << std::strerror(errno)
                  << std::endl;
        return;
    }

    struct flock lock{};

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        std::cerr << "Failed to acquire file lock: "
                  << std::strerror(errno)
                  << std::endl;
        close(fd);
        return;
    }

    std::cout << "File write lock acquired successfully."
              << std::endl;

    const char* message =
        "Telemetry log protected by Linux file locking.\n";

    ssize_t bytesWritten =
        write(fd, message, std::strlen(message));

    if (bytesWritten == -1) {
        std::cerr << "Failed to write locked file."
                  << std::endl;
    } else {
        std::cout << "Locked file written successfully. Bytes: "
                  << bytesWritten
                  << std::endl;
    }

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        std::cerr << "Failed to release file lock."
                  << std::endl;
    } else {
        std::cout << "File lock released successfully."
                  << std::endl;
    }

    close(fd);

    std::cout << "File locking test completed."
              << std::endl;
}
