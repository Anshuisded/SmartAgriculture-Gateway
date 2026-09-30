#include "network/TcpClient.h"
#include "sensor/SensorSimulator.h"

#include <iostream>
#include <sstream>

int main() {

    SensorSimulator sensor("NODE_01");
    SensorData data = sensor.generateReading();

    TcpClient client("127.0.0.1", 5000);

    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to gateway.\n";
        return 1;
    }

    std::ostringstream telemetry;

    telemetry << data.nodeId
              << "|soil_moisture=" << data.soilMoisture
              << "|temperature=" << data.temperature
              << "|humidity=" << data.humidity
              << "|battery=" << data.batteryLevel
              << "|status=" << data.status;

    if (!client.sendData(telemetry.str())) {
        std::cerr << "Failed to send telemetry.\n";
        return 1;
    }

    std::cout << "Telemetry sent successfully.\n";

    return 0;
}
