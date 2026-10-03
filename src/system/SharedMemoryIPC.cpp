#include "system/SharedMemoryIPC.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

void SharedMemoryIPC::runTest() {

    const std::size_t SHARED_SIZE = 256;

    char* sharedMemory = static_cast<char*>(
        mmap(nullptr,
             SHARED_SIZE,
             PROT_READ | PROT_WRITE,
             MAP_SHARED | MAP_ANONYMOUS,
             -1,
             0)
    );

    if (sharedMemory == MAP_FAILED) {
        std::cerr << "Failed to create shared memory.\n";
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Failed to create child process.\n";
        munmap(sharedMemory, SHARED_SIZE);
        return;
    }

    if (pid == 0) {

        const char* message =
            "Telemetry data from shared-memory sensor node";

        std::strncpy(
            sharedMemory,
            message,
            SHARED_SIZE - 1
        );

        sharedMemory[SHARED_SIZE - 1] = '\0';

        std::cout << "Child wrote: "
                  << sharedMemory
                  << std::endl;

        _exit(0);
    }

    waitpid(pid, nullptr, 0);

    std::cout << "Parent read: "
              << sharedMemory
              << std::endl;

    munmap(sharedMemory, SHARED_SIZE);

    std::cout << "Shared memory IPC test completed."
              << std::endl;
}
