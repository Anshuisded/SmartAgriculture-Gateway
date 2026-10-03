#include "system/MemoryMapDemo.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

void MemoryMapDemo::runTest() {

    const char* fileName = "logs/mmap_test.log";
    const char* message = "Telemetry shared through memory mapping.";

    int fd = open(fileName, O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        std::cerr << "Failed to open mmap file." << std::endl;
        return;
    }

    const std::size_t size = 4096;

    if (ftruncate(fd, size) == -1) {
        std::cerr << "Failed to resize mmap file." << std::endl;
        close(fd);
        return;
    }

    void* mappedMemory = mmap(
        nullptr,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );

    if (mappedMemory == MAP_FAILED) {
        std::cerr << "mmap failed." << std::endl;
        close(fd);
        return;
    }

    std::memcpy(mappedMemory, message, std::strlen(message) + 1);

    msync(mappedMemory, size, MS_SYNC);

    std::cout << "Memory mapping created successfully." << std::endl;
    std::cout << "Mapped telemetry: "
              << static_cast<char*>(mappedMemory)
              << std::endl;

    munmap(mappedMemory, size);
    close(fd);

    std::cout << "Memory mapping test completed." << std::endl;
}
