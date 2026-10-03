#include "system/FileLockDemo.h"

#include <iostream>

int main() {
    std::cout << "=== File Locking Test ===" << std::endl;

    FileLockDemo demo;
    demo.runTest();

    std::cout << "File locking test completed successfully."
              << std::endl;

    return 0;
}
