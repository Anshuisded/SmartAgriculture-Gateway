#include "system/AsyncIODemo.h"

#include <aio.h>
#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>

void AsyncIODemo::runTest() {

    const char* fileName = "logs/async_io_test.log";

    int fd = open(fileName, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1) {
        std::cerr << "Failed to open file: "
                  << std::strerror(errno) << std::endl;
        return;
    }

    char message[] =
        "Telemetry data written using asynchronous I/O.\n";

    struct aiocb request{};

    request.aio_fildes = fd;
    request.aio_buf = message;
    request.aio_nbytes = std::strlen(message);
    request.aio_offset = 0;

    if (aio_write(&request) == -1) {
        std::cerr << "Failed to start asynchronous write: "
                  << std::strerror(errno) << std::endl;
        close(fd);
        return;
    }

    std::cout << "Asynchronous write started successfully."
              << std::endl;

    while (aio_error(&request) == EINPROGRESS) {
    }

    int result = aio_error(&request);

    if (result != 0) {
        std::cerr << "Asynchronous write failed: "
                  << std::strerror(result) << std::endl;
        close(fd);
        return;
    }

    ssize_t bytesWritten = aio_return(&request);

    std::cout << "Asynchronous write completed."
              << std::endl;

    std::cout << "Bytes written: "
              << bytesWritten << std::endl;

    close(fd);

    std::cout << "Asynchronous I/O test completed."
              << std::endl;
}
