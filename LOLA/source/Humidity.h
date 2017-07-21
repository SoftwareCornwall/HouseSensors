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
    RTIMU *imu;
    RTHumidity *humidity;
    std::unique_ptr<RTIMUSettings> settings;
};

#endif
