#include "monitoring/NodeHealthMonitor.h"

#include <iostream>
#include <thread>
#include <chrono>

int main() {

    NodeHealthMonitor monitor;

    monitor.updateNode("NODE_01");

    if (monitor.isNodeActive("NODE_01", 5)) {
        std::cout << "Active node test: PASS\n";
    } else {
        std::cout << "Active node test: FAIL\n";
    }

    if (!monitor.isNodeActive("NODE_UNKNOWN", 5)) {
        std::cout << "Unknown node test: PASS\n";
    } else {
        std::cout << "Unknown node test: FAIL\n";
    }

    std::this_thread::sleep_for(
        std::chrono::seconds(2)
    );

    if (monitor.isNodeActive("NODE_01", 1)) {
        std::cout << "Timeout detection test: FAIL\n";
    } else {
        std::cout << "Timeout detection test: PASS\n";
    }

    return 0;
}
