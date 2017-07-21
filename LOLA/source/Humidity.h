#ifndef HUMIDITY_DEFINED
#define HUMIDITY_DEFINED

#include <RTIMULib.h>
#include <memory>
#include <string>
#include <iostream>
#include <exception>

struct sensorData_t
{
    float temperature;
    float humidity;
};

class Humidity
{
public:
    Humidity();
    bool GetSensorData(sensorData_t* sensorData);
private:
    std::unique_ptr<RTIMU> imu;
    std::unique_ptr<RTHumidity> humidity;
    std::unique_ptr<RTIMUSettings> settings;
};

#endif
