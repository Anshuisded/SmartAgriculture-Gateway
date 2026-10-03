#include "system/SharedMemoryIPC.h"

#include <iostream>

int main() {
    std::cout << "=== Shared Memory IPC Test ===\n";

    SharedMemoryIPC ipc;
    ipc.runTest();

    std::cout << "Shared memory IPC test completed successfully.\n";

    return 0;
}
