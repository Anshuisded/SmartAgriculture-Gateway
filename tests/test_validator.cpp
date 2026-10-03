#include "processing/TelemetryValidator.h"
#include "sensor/SensorData.h"

#include <iostream>

int main() {

    TelemetryValidator validator;

    // Test 1: Valid telemetry
    SensorData validData;
    validData.nodeId = "NODE_01";
    validData.soilMoisture = 50.0;
    validData.temperature = 25.0;
    validData.humidity = 60.0;
    validData.batteryLevel = 80.0;

    if (!validator.validate(validData)) {
        std::cerr << "FAIL: Valid telemetry was rejected.\n";
        return 1;
    }

    std::cout << "PASS: Valid telemetry accepted.\n";

    // Test 2: Invalid soil moisture
    SensorData invalidMoisture = validData;
    invalidMoisture.soilMoisture = 120.0;

    if (validator.validate(invalidMoisture)) {
        std::cerr << "FAIL: Invalid soil moisture was accepted.\n";
        return 1;
    }

    std::cout << "PASS: Invalid soil moisture rejected.\n";

    // Test 3: Invalid temperature
    SensorData invalidTemperature = validData;
    invalidTemperature.temperature = 100.0;

    if (validator.validate(invalidTemperature)) {
        std::cerr << "FAIL: Invalid temperature was accepted.\n";
        return 1;
    }

    std::cout << "PASS: Invalid temperature rejected.\n";

    // Test 4: Invalid humidity
    SensorData invalidHumidity = validData;
    invalidHumidity.humidity = -10.0;

    if (validator.validate(invalidHumidity)) {
        std::cerr << "FAIL: Invalid humidity was accepted.\n";
        return 1;
    }

    std::cout << "PASS: Invalid humidity rejected.\n";

    // Test 5: Invalid battery
    SensorData invalidBattery = validData;
    invalidBattery.batteryLevel = 150.0;

    if (validator.validate(invalidBattery)) {
        std::cerr << "FAIL: Invalid battery level was accepted.\n";
        return 1;
    }

    std::cout << "PASS: Invalid battery level rejected.\n";

    std::cout << "Telemetry validator test completed successfully.\n";

    return 0;
}
