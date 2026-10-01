#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <mutex>
#include <string>

class Logger {
public:
    explicit Logger(const std::string& filename);

    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

private:
    std::ofstream logFile;
    std::mutex mutex;

    void write(
        const std::string& level,
        const std::string& message
    );
};

#endif
