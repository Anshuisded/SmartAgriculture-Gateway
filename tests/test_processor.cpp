#include "processing/TelemetryProcessor.h"

#include <iostream>

int main() {

    TelemetryProcessor processor;

    SensorData data;
    data.nodeId = "NODE_01";
    data.soilMoisture = 25.0;
    data.temperature = 28.0;
    data.humidity = 65.0;
    data.batteryLevel = 90.0;

    std::string result = processor.process(data);

    std::cout << result << '\n';

    return 0;
}
