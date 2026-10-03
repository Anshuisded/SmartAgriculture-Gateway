#include "system/SemaphoreIPC.h"

#include <iostream>

int main() {
    std::cout << "=== Semaphore IPC Test ===\n";

    SemaphoreIPC ipc;
    ipc.runTest();

    std::cout << "Semaphore IPC test completed successfully.\n";

    return 0;
}
