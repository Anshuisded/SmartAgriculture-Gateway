#include "processing/TelemetryValidator.h"

#include <iostream>

int main() {

    TelemetryValidator validator;

    SensorData validData;
    validData.nodeId = "NODE_01";
    validData.soilMoisture = 50.0;
    validData.temperature = 25.0;
    validData.humidity = 60.0;
    validData.batteryLevel = 90.0;

    SensorData invalidData = validData;
    invalidData.soilMoisture = 150.0;

    if (!validator.validate(validData)) {
        std::cerr << "Valid telemetry was rejected.\n";
        return 1;
    }

    if (validator.validate(invalidData)) {
        std::cerr << "Invalid telemetry was accepted.\n";
        return 1;
    }

    std::cout << "Telemetry validation test passed.\n";

    return 0;
}
