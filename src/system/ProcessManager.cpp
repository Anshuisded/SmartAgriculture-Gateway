#include "system/ProcessManager.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

void ProcessManager::runWorker(const char* workerName) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Failed to create process for "
                  << workerName << ".\n";
        return;
    }

    if (pid == 0) {
        std::cout << "Worker process started: "
                  << workerName
                  << " | PID=" << getpid()
                  << " | Parent PID=" << getppid()
                  << std::endl;

        _exit(0);
    }

    waitpid(pid, nullptr, 0);

    std::cout << "Worker process completed: "
              << workerName
              << " | Child PID=" << pid
              << "\n";
}

void ProcessManager::runWorkers(int count) {
    for (int i = 1; i <= count; ++i) {
        std::string workerName =
            "AGRI_WORKER_" + std::to_string(i);

        runWorker(workerName.c_str());
    }
}
