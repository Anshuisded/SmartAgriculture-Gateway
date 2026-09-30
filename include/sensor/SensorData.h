#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <string>


struct SensorData{
std::string nodeId;
std::string timestamp;


double soilMoisture;
double temperature;
double humidity;
double batteryLevel;


std::string status;

};

#endif
