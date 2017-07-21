#ifndef HUMIDITY_DEFINED
#define HUMIDITY

#include <RTIMULib.h>
#include <memory>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

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
    unique_ptr<RTIMUSettings> settings;
};

#endif
