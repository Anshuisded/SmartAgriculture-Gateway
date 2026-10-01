#include "processing/TelemetryValidator.h"
#include <iostream>

int main() {

    TelemetryValidator validator;

    SensorData validData;
    validData.nodeId = "NODE_01";
    validData.soilMoisture = 45.0;
    validData.temperature = 28.0;
    validData.humidity = 65.0;
    validData.batteryLevel = 90.0;

    SensorData invalidData;
    invalidData.nodeId = "NODE_02";
    invalidData.soilMoisture = 150.0;
    invalidData.temperature = 28.0;
    invalidData.humidity = 65.0;
    invalidData.batteryLevel = 90.0;

    if (validator.validate(validData)) {
        std::cout << "Valid telemetry test: PASS\n";
    } else {
        std::cout << "Valid telemetry test: FAIL\n";
    }

    if (!validator.validate(invalidData)) {
        std::cout << "Invalid telemetry test: PASS\n";
    } else {
        std::cout << "Invalid telemetry test: FAIL\n";
    }

    return 0;
}
