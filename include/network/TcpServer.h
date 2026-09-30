#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>

class TcpServer {
public:
    explicit TcpServer(int port);
    ~TcpServer();

    void start();

private:
    int port;
    int serverSocket;

    void handleClient(int clientSocket);
};

#endif
