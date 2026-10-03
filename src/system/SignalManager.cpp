#include "system/SignalManager.h"

#include <csignal>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

namespace {
volatile sig_atomic_t signalReceived = 0;

void handleSignal(int signalNumber) {
    if (signalNumber == SIGUSR1) {
        signalReceived = 1;
    }
}
}

void SignalManager::runTest() {

    struct sigaction action{};
    action.sa_handler = handleSignal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGUSR1, &action, nullptr) == -1) {
        std::cerr << "Failed to register signal handler.\n";
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Failed to create child process.\n";
        return;
    }

    if (pid == 0) {
        sleep(1);

        kill(getppid(), SIGUSR1);

        _exit(0);
    }

    waitpid(pid, nullptr, 0);

    if (signalReceived) {
        std::cout << "SIGUSR1 received: Telemetry processing signal handled."
                  << std::endl;
    }

    std::cout << "Signal IPC test completed." << std::endl;
}
