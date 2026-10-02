#include "alerts/AlertEngine.h"
#include "sensor/SensorData.h"

#include <iostream>
#include <vector>

int main() {

    AlertEngine engine;

    SensorData data;

    data.nodeId = "NODE_ALERT";
    data.soilMoisture = 20.0;
    data.temperature = 45.0;
    data.humidity = 70.0;
    data.batteryLevel = 15.0;

    std::vector<std::string> alerts =
        engine.generateAlerts(data);

    for (const auto& alert : alerts) {
        std::cout << alert << '\n';
    }

    if (alerts.size() == 3) {
        std::cout << "Alert engine test passed.\n";
        return 0;
    }

    std::cout << "Alert engine test failed.\n";
    return 1;
}
