#include "system/PipeIPC.h"

#include <unistd.h>
#include <sys/wait.h>

#include <cstring>
#include <iostream>

void PipeIPC::runTest() {
    int pipeFd[2];

    if (pipe(pipeFd) == -1) {
        std::cerr << "Failed to create pipe.\n";
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Failed to create child process.\n";
        return;
    }

    if (pid == 0) {
        close(pipeFd[0]);

        const char* message =
            "Telemetry message from sensor worker";

        write(pipeFd[1], message, std::strlen(message));

        close(pipeFd[1]);
        _exit(0);
    }

    close(pipeFd[1]);

    char buffer[128] = {};

    ssize_t bytesRead =
        read(pipeFd[0], buffer, sizeof(buffer) - 1);

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';

        std::cout << "IPC message received: "
                  << buffer << "\n";
    }

    close(pipeFd[0]);

    waitpid(pid, nullptr, 0);

    std::cout << "Pipe IPC test completed.\n";
}
