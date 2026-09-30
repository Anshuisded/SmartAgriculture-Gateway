#include <iostream>
#include "sensor/SensorSimulator.h"

int main() {

    SensorSimulator sensor("NODE_01");

    for (int i = 0; i < 5; ++i) {

        SensorData data = sensor.generateReading();

std::cout << "Node ID: " << data.nodeId << '\n';
        std::cout << "Timestamp: " << data.timestamp << '\n';
        std::cout << "Soil Moisture: " << data.soilMoisture << "%\n";
        std::cout << "Temperature: " << data.temperature << " C\n";
        std::cout << "Humidity: " << data.humidity << "%\n";
        std::cout << "Battery: " << data.batteryLevel << "%\n";
        std::cout << "Status: " << data.status << '\n';
    }

return 0;
}

