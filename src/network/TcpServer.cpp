#include "network/TcpServer.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
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

        std::cerr << "Failed to listen on port "
                  << port << ".\n";

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

        std::thread(&TcpServer::handleClient,this,clientSocket).detach();
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

    if (bytesReceived > 0) {

        buffer[bytesReceived] = '\0';

        std::cout << "Received telemetry:\n";
        std::cout << buffer << '\n';

    } else if (bytesReceived == 0) {

        std::cout << "Sensor node disconnected.\n";

    } else {

        std::cerr << "Error receiving telemetry.\n";
    }

    close(clientSocket);
}
