#include "system/MessageQueueIPC.h"

#include <iostream>

int main() {
    std::cout << "=== Message Queue IPC Test ===\n";

    MessageQueueIPC ipc;
    ipc.runTest();

    std::cout << "Message queue IPC test completed successfully.\n";

    return 0;
}
