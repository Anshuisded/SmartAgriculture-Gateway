#include "logging/Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Warning: Could not open log file: "
                  << filename << '\n';
    }
}

void Logger::info(const std::string& message) {
    write("INFO", message);
}

void Logger::warning(const std::string& message) {
    write("WARNING", message);
}

void Logger::error(const std::string& message) {
    write("ERROR", message);
}

void Logger::write(
    const std::string& level,
    const std::string& message) {

    std::lock_guard<std::mutex> lock(mutex);

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&currentTime);

    if (!logFile.is_open()) {
        return;
    }

    logFile << std::put_time(localTime, "%Y-%m-%d %H:%M:%S")
            << " [" << level << "] "
            << message << '\n';

    logFile.flush();
}
