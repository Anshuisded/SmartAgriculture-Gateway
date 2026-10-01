#ifndef ALERT_ENGINE_H
#define ALERT_ENGINE_H

#include "sensor/SensorData.h"
#include <string>
#include <vector>

class AlertEngine {
public:
    std::vector<std::string> generateAlerts(
        const SensorData& data) const;
};

#endif
