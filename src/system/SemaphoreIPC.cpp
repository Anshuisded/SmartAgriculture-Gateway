#include "system/SemaphoreIPC.h"

#include <iostream>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <cstring>

namespace {
    struct SharedData {
        sem_t semaphore;
        char message[128];
    };
}

void SemaphoreIPC::runTest() {

    SharedData* sharedData = static_cast<SharedData*>(
        mmap(nullptr,
             sizeof(SharedData),
             PROT_READ | PROT_WRITE,
             MAP_SHARED | MAP_ANONYMOUS,
             -1,
             0)
    );

    if (sharedData == MAP_FAILED) {
        std::cerr << "Failed to create shared memory.\n";
        return;
    }

    if (sem_init(&sharedData->semaphore, 1, 0) == -1) {
        std::cerr << "Failed to initialize semaphore.\n";
        munmap(sharedData, sizeof(SharedData));
        return;
    }

    std::memset(sharedData->message, 0, sizeof(sharedData->message));

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Failed to create child process.\n";
        sem_destroy(&sharedData->semaphore);
        munmap(sharedData, sizeof(SharedData));
        return;
    }

    if (pid == 0) {

        const char* message =
            "Telemetry processed by semaphore worker";

        std::strncpy(
            sharedData->message,
            message,
            sizeof(sharedData->message) - 1
        );

        std::cout << "Child wrote: "
                  << sharedData->message
                  << std::endl;

        sem_post(&sharedData->semaphore);

        _exit(0);
    }

    sem_wait(&sharedData->semaphore);

    std::cout << "Parent read: "
              << sharedData->message
              << std::endl;

    waitpid(pid, nullptr, 0);

    sem_destroy(&sharedData->semaphore);
    munmap(sharedData, sizeof(SharedData));

    std::cout << "Semaphore IPC test completed."
              << std::endl;
}
