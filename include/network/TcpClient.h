#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>

class TcpClient {
public:
    TcpClient(const std::string& host, int port);

    bool connectToServer();
    bool sendData(const std::string& data);

private:
    std::string host;
    int port;
    int clientSocket;
};

#endif
