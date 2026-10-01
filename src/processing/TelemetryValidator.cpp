#include "processing/TelemetryValidator.h"

bool TelemetryValidator::validate(const SensorData& data) const {

    if (data.nodeId.empty()) {
        return false;
    }

    if (data.soilMoisture < 0.0 || data.soilMoisture > 100.0) {
        return false;
    }

    if (data.temperature < -50.0 || data.temperature > 80.0) {
        return false;
    }

    if (data.humidity < 0.0 || data.humidity > 100.0) {
        return false;
    }

    if (data.batteryLevel < 0.0 || data.batteryLevel > 100.0) {
        return false;
    }

    return true;
}
