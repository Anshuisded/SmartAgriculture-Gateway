#include "system/MemoryMapDemo.h"

#include <iostream>

int main() {

    std::cout << "=== Memory Mapping Test ===" << std::endl;

    MemoryMapDemo demo;
    demo.runTest();

    std::cout << "Memory mapping test completed successfully."
              << std::endl;

    return 0;
}
