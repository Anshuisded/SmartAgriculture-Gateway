#include "network/TcpServer.h"

#include "alerts/AlertEngine.h"
#include "monitoring/NodeHealthMonitor.h"
#include "processing/TelemetryProcessor.h"
#include "processing/TelemetryValidator.h"
#include "sensor/SensorData.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>

TcpServer::TcpServer(int port)
    : port(port), serverSocket(-1) {
}

TcpServer::~TcpServer() {
    if (serverSocket != -1) {
        close(serverSocket);
    }
}

void TcpServer::start() {

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        std::cerr << "Failed to create server socket.\n";
        return;
    }

    int reuse = 1;

    if (setsockopt(
            serverSocket,
            SOL_SOCKET,
            SO_REUSEADDR,
            &reuse,
            sizeof(reuse)) < 0) {

        std::cerr << "Failed to configure socket.\n";
        close(serverSocket);
        serverSocket = -1;
        return;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(
            serverSocket,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)) < 0) {

        std::cerr << "Failed to bind server socket.\n";
        close(serverSocket);
        serverSocket = -1;
        return;
    }

    if (listen(serverSocket, 10) < 0) {

        std::cerr << "Failed to listen on server socket.\n";
        close(serverSocket);
        serverSocket = -1;
        return;
    }

    std::cout << "TCP Gateway listening on port "
              << port << "...\n";

    while (true) {

        sockaddr_in clientAddress{};
        socklen_t clientLength = sizeof(clientAddress);

        int clientSocket = accept(
            serverSocket,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientLength);

        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection.\n";
            continue;
        }

        std::cout << "Sensor node connected.\n";

        std::thread clientThread(
            &TcpServer::handleClient,
            this,
            clientSocket);

        clientThread.detach();
    }
}

void TcpServer::handleClient(int clientSocket) {

    char buffer[1024];

    std::memset(buffer, 0, sizeof(buffer));

    ssize_t bytesReceived = recv(
        clientSocket,
        buffer,
        sizeof(buffer) - 1,
        0);

    if (bytesReceived <= 0) {

        if (bytesReceived == 0) {
            std::cout << "Sensor node disconnected.\n";
        } else {
            std::cerr << "Error receiving telemetry.\n";
        }

        close(clientSocket);
        return;
    }

    buffer[bytesReceived] = '\0';

    std::string message(buffer);

    std::cout << "Received telemetry:\n";
    std::cout << message << '\n';

    SensorData data;

    std::stringstream stream(message);
    std::string field;

    while (std::getline(stream, field, '|')) {

        std::size_t separator = field.find('=');

        if (separator == std::string::npos) {

            if (data.nodeId.empty()) {
                data.nodeId = field;
            }

            continue;
        }

        std::string key = field.substr(0, separator);
        std::string value = field.substr(separator + 1);

        try {

            if (key == "soil_moisture") {
                data.soilMoisture = std::stod(value);
            }
            else if (key == "temperature") {
                data.temperature = std::stod(value);
            }
            else if (key == "humidity") {
                data.humidity = std::stod(value);
            }
            else if (key == "battery") {
                data.batteryLevel = std::stod(value);
            }
            else if (key == "status") {
                data.status = value;
            }

        } catch (const std::exception&) {

            std::cerr << "Invalid numeric telemetry value.\n";
            close(clientSocket);
            return;
        }
    }

    TelemetryValidator validator;
    TelemetryProcessor processor;
    AlertEngine alertEngine;
    NodeHealthMonitor healthMonitor;

    healthMonitor.updateNode(data.nodeId);


    std::cout << "Node health: ACTIVE (" << data.nodeId << ")\n";
    if (!validator.validate(data)) {

        std::cout << "Telemetry validation: FAILED\n";

    } else {

        std::cout << "Telemetry validation: PASSED\n";

        std::cout << "Processed telemetry:\n";
        std::cout << processor.process(data) << '\n';

        std::vector<std::string> alerts =
            alertEngine.generateAlerts(data);

        if (alerts.empty()) {

            std::cout << "Alerts: NONE\n";

        } else {

            std::cout << "Alerts generated: "
                      << alerts.size() << '\n';

            for (const auto& alert : alerts) {
                std::cout << "ALERT: "
                          << alert << '\n';
            }
        }
    }

    close(clientSocket);
}
