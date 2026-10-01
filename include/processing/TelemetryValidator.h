#ifndef TELEMETRY_VALIDATOR_H
#define TELEMETRY_VALIDATOR_H

#include "sensor/SensorData.h"

class TelemetryValidator {
public:
    bool validate(const SensorData& data) const;
};

#endif
