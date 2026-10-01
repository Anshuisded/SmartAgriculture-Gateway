#include "alerts/AlertEngine.h"

#include <iostream>
#include <vector>

int main() {

    AlertEngine engine;

    SensorData data;
    data.nodeId = "NODE_01";
    data.soilMoisture = 20.0;
    data.temperature = 42.0;
    data.humidity = 65.0;
    data.batteryLevel = 15.0;

    std::vector<std::string> alerts =
        engine.generateAlerts(data);

    std::cout << "Alerts generated: "
              << alerts.size() << '\n';

    for (const auto& alert : alerts) {
        std::cout << "ALERT: " << alert << '\n';
    }

    return 0;
}
