#include "system/ProcessManager.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

void ProcessManager::runTest() {

    std::cout << "=== Process Management Test ===" << std::endl;

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Failed to create child process." << std::endl;
        return;
    }

    if (pid == 0) {
        std::cout << "Child process created. PID: "
                  << getpid() << std::endl;

        execlp("echo", "echo",
               "Child process executed using exec().",
               static_cast<char*>(nullptr));

        std::cerr << "exec() failed." << std::endl;
        _exit(EXIT_FAILURE);
    }

    int status = 0;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        std::cout << "Child process exited with status: "
                  << WEXITSTATUS(status) << std::endl;
    }

    std::cout << "Process management test completed."
              << std::endl;
}
