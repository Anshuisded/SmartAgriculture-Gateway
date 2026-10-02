#include "processing/TelemetryProcessor.h"

#include <iostream>

int main() {

    SensorData data;

    data.nodeId = "NODE_TEST";
    data.soilMoisture = 25.0;
    data.temperature = 28.0;
    data.humidity = 65.0;
    data.batteryLevel = 85.0;

    TelemetryProcessor processor;

    std::cout << processor.process(data);

    return 0;
}
