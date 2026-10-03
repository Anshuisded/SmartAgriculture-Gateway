#include "system/ProcessManager.h"

#include <iostream>

int main() {

    std::cout << "=== Process Manager Test ===" << std::endl;

    ProcessManager manager;
    manager.runTest();

    std::cout << "Process manager test completed successfully."
              << std::endl;

    return 0;
}
