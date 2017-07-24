#ifndef HUMIDITY_DEFINED
#define HUMIDITY_DEFINED

#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include <RTIMULib.h>

struct SensorData
{
    float temperature;
    float humidity;
};

class Sensor
{
public:
    Sensor();
    bool getData(SensorData* sensorData);
private:
    const std::unique_ptr<RTIMUSettings> settings_ = std::unique_ptr<RTIMUSettings>(new RTIMUSettings("RTIMULib"));
    std::unique_ptr<RTIMU> imu_;
    std::unique_ptr<RTHumidity> humidity_;
};

#endif
