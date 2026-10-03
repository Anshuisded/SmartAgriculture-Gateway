#include "system/AsyncIODemo.h"

#include <iostream>

int main() {
    std::cout << "=== Asynchronous I/O Test ===" << std::endl;

    AsyncIODemo demo;
    demo.runTest();

    std::cout << "Asynchronous I/O test completed successfully."
              << std::endl;

    return 0;
}
