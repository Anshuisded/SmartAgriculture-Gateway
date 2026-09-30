#include "sensor/SensorSimulator.h"

#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::cout << "Smart Agriculture Gateway\n";
    std::cout << "=========================\n\n";

    std::vector<std::unique_ptr<SensorSimulator>> sensors;

    sensors.push_back(std::make_unique<SensorSimulator>("NODE_01"));
    sensors.push_back(std::make_unique<SensorSimulator>("NODE_02"));
    sensors.push_back(std::make_unique<SensorSimulator>("NODE_03"));

    for (const auto& sensor : sensors) {
        SensorData data = sensor->generateReading();

        std::cout << "Node ID: " << data.nodeId << '\n';
        std::cout << "Timestamp: " << data.timestamp << '\n';
        std::cout << "Soil Moisture: " << data.soilMoisture << "%\n";
        std::cout << "Temperature: " << data.temperature << " C\n";
        std::cout << "Humidity: " << data.humidity << "%\n";
        std::cout << "Battery: " << data.batteryLevel << "%\n";
        std::cout << "Status: " << data.status << "\n";
        std::cout << "-----------------------------\n";
    }

    return 0;
}
