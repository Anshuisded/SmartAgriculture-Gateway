#include "system/FileDescriptorDemo.h"

#include <iostream>

int main() {

    std::cout << "=== File Descriptor Test ===" << std::endl;

    FileDescriptorDemo demo;
    demo.runTest();

    std::cout << "File descriptor test completed successfully."
              << std::endl;

    return 0;
}
