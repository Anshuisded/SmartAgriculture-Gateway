#include "system/MessageQueueIPC.h"

#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>

void MessageQueueIPC::runTest() {

    const char* queueName = "/agri_telemetry_queue";

    struct mq_attr attributes{};
    attributes.mq_flags = 0;
    attributes.mq_maxmsg = 10;
    attributes.mq_msgsize = 128;
    attributes.mq_curmsgs = 0;

    mqd_t queue = mq_open(
        queueName,
        O_CREAT | O_RDWR,
        0666,
        &attributes
    );

    if (queue == (mqd_t)-1) {
        std::cerr << "Failed to create message queue.\n";
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Failed to create child process.\n";
        mq_close(queue);
        mq_unlink(queueName);
        return;
    }

    if (pid == 0) {

        const char* message =
            "Telemetry message from sensor node";

        if (mq_send(queue, message, std::strlen(message) + 1, 0) == -1) {
            std::cerr << "Child failed to send message.\n";
            _exit(1);
        }

        std::cout << "Child sent: "
                  << message
                  << std::endl;

        mq_close(queue);
        _exit(0);
    }

    char buffer[128]{};

    ssize_t bytesReceived = mq_receive(
        queue,
        buffer,
        sizeof(buffer),
        nullptr
    );

    if (bytesReceived == -1) {
        std::cerr << "Parent failed to receive message.\n";
    } else {
        std::cout << "Parent received: "
                  << buffer
                  << std::endl;
    }

    waitpid(pid, nullptr, 0);

    mq_close(queue);
    mq_unlink(queueName);

    std::cout << "Message queue IPC test completed."
              << std::endl;
}
