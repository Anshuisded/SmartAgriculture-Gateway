#include "system/ProcessManager.h"

#include <iostream>

int main() {
    std::cout << "=== Process Manager Test ===\n";

    ProcessManager manager;

    manager.runWorkers(3);

    std::cout << "Process manager test completed.\n";

    return 0;
}
