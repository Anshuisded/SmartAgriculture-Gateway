#include "network/TcpClient.h"

#include <iostream>
#include <string>

int main() {

    TcpClient client("127.0.0.1", 5000);

    if (!client.connectToServer()) {
        std::cerr << "Could not connect to gateway.\n";
        return 1;
    }

    std::string telemetry =
        "NODE_01|soil_moisture=28.5|temperature=31.2|humidity=67.4|battery=91.0";

    if (client.sendData(telemetry)) {
        std::cout << "Telemetry sent successfully.\n";
    } else {
        std::cerr << "Failed to send telemetry.\n";
        return 1;
    }

    return 0;
}
