#include "monitoring/NodeHealthMonitor.h"

void NodeHealthMonitor::updateNode(const std::string& nodeId) {

    std::lock_guard<std::mutex> lock(mutex);

    lastSeen[nodeId] = std::chrono::steady_clock::now();
}

bool NodeHealthMonitor::isNodeActive(
    const std::string& nodeId,
    int timeoutSeconds) const {

    std::lock_guard<std::mutex> lock(mutex);

    auto it = lastSeen.find(nodeId);

    if (it == lastSeen.end()) {
        return false;
    }

    auto now = std::chrono::steady_clock::now();

    auto elapsed =
        std::chrono::duration_cast<std::chrono::seconds>(
            now - it->second
        ).count();

    return elapsed <= timeoutSeconds;
}
