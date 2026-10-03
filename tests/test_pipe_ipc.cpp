#include "system/PipeIPC.h"

#include <iostream>

int main() {
    std::cout << "=== Pipe IPC Test ===\n";

    PipeIPC ipc;
    ipc.runTest();

    std::cout << "Pipe IPC test completed successfully.\n";

    return 0;
}
