#include "SensorSimulator.h"

#include <random>
#include <chrono>
#include <ctime>
#include<iomanip>
#include <sstream>


SensorSimulator::SensorSimulator(const std::string& nodeId)
: nodeId(nodeId){
}
SensorData SensorSimulator::generateReading(){
static std::random_device rd;
static std::mt19937 generator(rd());

std::uniform_real_distribution<double>moisture(20.0,80.0);
std::uniform_real_distribution<double>temperature(20.0,35.0);
std::uniform_real_distribution<double>humidity(40.0,90.0);
std::uniform_real_distribution<double>battery(60.0,100.0);


auto now = std::chrono::system_clock::now();
    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::stringstream timestampStream;

    timestampStream << std::put_time(
        std::localtime(&currentTime),
        "%Y-%m-%d %H:%M:%S"
    );

    SensorData data;

    data.nodeId = nodeId;
    data.timestamp = timestampStream.str();
    data.soilMoisture = moisture(generator);
    data.temperature = temperature(generator);
    data.humidity = humidity(generator);
    data.batteryLevel = battery(generator);

    if (data.soilMoisture < 30.0) {
        data.status = "LOW_MOISTURE";
    } else {
        data.status = "NORMAL";
    }

    return data;
}
