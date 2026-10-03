#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <sys/types.h>

class ProcessManager {
public:
    void runWorker(const char* workerName);
    void runWorkers(int count);
};

#endif
