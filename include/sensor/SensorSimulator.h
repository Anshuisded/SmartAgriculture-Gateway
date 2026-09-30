#ifndef SENSOR_SIMULATOR_H
#define SENSOR_SIMULATOR_H

#include "SensorData.h"
#include <string>

class SensorSimulator{
public:
explicit SensorSimulator(const std::string& nodeId);

SensorData generateReading();

private:
std::string nodeId;
};

#endif


