#include "system/SignalManager.h"

#include <iostream>

int main() {
    std::cout << "=== Signal Manager Test ===\n";

    SignalManager manager;
    manager.runTest();

    std::cout << "Signal manager test completed successfully.\n";

    return 0;
}
