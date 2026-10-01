#include "processing/TelemetryProcessor.h"

#include <sstream>

std::string TelemetryProcessor::process(const SensorData& data) const {

    std::string moistureStatus;

    if (data.soilMoisture < 30.0) {
        moistureStatus = "DRY";
    } else if (data.soilMoisture <= 60.0) {
        moistureStatus = "OPTIMAL";
    } else {
        moistureStatus = "WET";
    }

    bool irrigationRequired = data.soilMoisture < 30.0;

    std::ostringstream result;

    result << "Node=" << data.nodeId
           << " | Moisture=" << data.soilMoisture << "%"
           << " | MoistureStatus=" << moistureStatus
           << " | Temperature=" << data.temperature << "C"
           << " | Humidity=" << data.humidity << "%"
           << " | Battery=" << data.batteryLevel << "%"
           << " | Irrigation="
           << (irrigationRequired ? "REQUIRED" : "NOT_REQUIRED");

    return result.str();
}
