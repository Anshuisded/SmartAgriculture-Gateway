#include "network/TcpServer.h"

#include <iostream>

int main() {

    std::cout << "Smart Agriculture Gateway\n";
    std::cout << "=========================\n";

    TcpServer server(5000);

    server.start();

    return 0;
}
