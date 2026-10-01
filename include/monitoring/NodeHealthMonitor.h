#ifndef NODE_HEALTH_MONITOR_H
#define NODE_HEALTH_MONITOR_H

#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>

class NodeHealthMonitor {
public:
    void updateNode(const std::string& nodeId);

    bool isNodeActive(
        const std::string& nodeId,
        int timeoutSeconds = 30
    ) const;

private:
    std::unordered_map<
        std::string,
        std::chrono::steady_clock::time_point
    > lastSeen;

    mutable std::mutex mutex;
};

#endif
