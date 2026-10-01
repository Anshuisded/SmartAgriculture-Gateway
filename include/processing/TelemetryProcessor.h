#ifndef TELEMETRY_PROCESSOR_H
#define TELEMETRY_PROCESSOR_H

#include "sensor/SensorData.h"
#include <string>

class TelemetryProcessor {
public:
    std::string process(const SensorData& data) const;
};

#endif
