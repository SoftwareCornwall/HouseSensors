#ifndef HUMIDITY_DEFINED
#define HUMIDITY_DEFINED

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
    bool setup();
    bool getData(SensorData* sensorData);
    std::string sensorDataToString(const SensorData& sensorData);
private:
    std::unique_ptr<RTIMUSettings> settings_;
    std::unique_ptr<RTIMU> imu_;
    std::unique_ptr<RTHumidity> humidity_;
    bool isSetUp_;
    unsigned long long getSecondsSinceEpoch();
};

#endif
