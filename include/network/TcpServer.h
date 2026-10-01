#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>
#include <thread>
#include "logging/Logger.h"

class TcpServer {
public:
    explicit TcpServer(int port);
    ~TcpServer();

    void start();

private:
    int port;
    int serverSocket;
Logger logger;


    void handleClient(int clientSocket);
};

#endif
