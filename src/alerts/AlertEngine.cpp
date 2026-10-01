#include "alerts/AlertEngine.h"

std::vector<std::string> AlertEngine::generateAlerts(
    const SensorData& data) const {

    std::vector<std::string> alerts;

    if (data.soilMoisture < 30.0) {
        alerts.push_back(
            "LOW_MOISTURE: Irrigation required"
        );
    }

    if (data.batteryLevel < 20.0) {
        alerts.push_back(
            "LOW_BATTERY: Sensor battery is low"
        );
    }

    if (data.temperature > 40.0) {
        alerts.push_back(
            "HIGH_TEMPERATURE: Temperature exceeds safe threshold"
        );
    }

    return alerts;
}
