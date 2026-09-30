#include "network/TcpClient.h"
#include "sensor/SensorSimulator.h"

#include <iostream>
#include <sstream>
#include <vector>

int main() {

    std::vector<std::string> nodeIds = {
        "NODE_01",
        "NODE_02",
        "NODE_03"
    };

    for (const auto& nodeId : nodeIds) {

        SensorSimulator sensor(nodeId);
        SensorData data = sensor.generateReading();

        TcpClient client("127.0.0.1", 5000);

        if (!client.connectToServer()) {
            std::cerr << "Failed to connect to gateway for "
                      << nodeId << ".\n";
            continue;
        }

        std::ostringstream telemetry;

        telemetry << data.nodeId
                  << "|soil_moisture=" << data.soilMoisture
                  << "|temperature=" << data.temperature
                  << "|humidity=" << data.humidity
                  << "|battery=" << data.batteryLevel
                  << "|status=" << data.status;

        if (!client.sendData(telemetry.str())) {
            std::cerr << "Failed to send telemetry for "
                      << nodeId << ".\n";
            continue;
        }

        std::cout << "Telemetry sent successfully from "
                  << nodeId << ".\n";
    }

    return 0;
}
