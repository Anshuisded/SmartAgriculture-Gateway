#include "processing/TelemetryProcessor.h"
#include "sensor/SensorData.h"

#include <iostream>
#include <string>

int main() {

    TelemetryProcessor processor;

    SensorData data;

    data.nodeId = "TEST_NODE";
    data.timestamp = "2026-10-03 11:00:00";
    data.soilMoisture = 25.0;
    data.temperature = 30.0;
    data.humidity = 65.0;
    data.batteryLevel = 85.0;
    data.status = "LOW_MOISTURE";

    std::string result = processor.process(data);

    if (result.empty()) {
        std::cerr << "FAIL: Processor returned empty result.\n";
        return 1;
    }

    std::cout << "PASS: Telemetry processed successfully.\n";
    std::cout << result << "\n";

    std::cout << "Telemetry processor test completed successfully.\n";

    return 0;
}
