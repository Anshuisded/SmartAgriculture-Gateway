#include "network/TcpClient.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

TcpClient::TcpClient(const std::string& host, int port)
    : host(host), port(port), clientSocket(-1) {
}

bool TcpClient::connectToServer() {

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        std::cerr << "Failed to create client socket.\n";
        return false;
    }

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(
            AF_INET,
            host.c_str(),
            &serverAddress.sin_addr) <= 0) {

        std::cerr << "Invalid server address.\n";
        close(clientSocket);
        clientSocket = -1;
        return false;
    }

    if (connect(
            clientSocket,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)) < 0) {

        std::cerr << "Failed to connect to gateway.\n";
        close(clientSocket);
        clientSocket = -1;
        return false;
    }

    return true;
}

bool TcpClient::sendData(const std::string& data) {

    if (clientSocket < 0) {
        std::cerr << "Client is not connected.\n";
        return false;
    }

    ssize_t bytesSent = send(
        clientSocket,
        data.c_str(),
        data.size(),
        0);

    if (bytesSent < 0) {
        std::cerr << "Failed to send telemetry.\n";
        return false;
    }

    return static_cast<std::size_t>(bytesSent) == data.size();
}
