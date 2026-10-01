#include "network/TcpClient.h"

#include <iostream>

int main() {

    TcpClient client("127.0.0.1", 5000);

    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to gateway.\n";
        return 1;
    }

    std::string telemetry =
        "NODE_ALERT"
        "|soil_moisture=20.0"
        "|temperature=42.0"
        "|humidity=65.0"
        "|battery=15.0"
        "|status=LOW_MOISTURE";

    if (!client.sendData(telemetry)) {
        std::cerr << "Failed to send alert telemetry.\n";
        return 1;
    }

    std::cout << "Alert test telemetry sent successfully.\n";

    return 0;
}
