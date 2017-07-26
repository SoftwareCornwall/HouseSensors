#ifndef IMU_CONTROLLER_DEFINED
#define IMU_CONTROLLER_DEFINED

#include "../Sensor/Sensor.h"
#include "../Curl/Curl.h"

class IMUController
{
public:
    IMUController();
    ~IMUController();
    bool setup();
    void run(const bool& executionCondition);
private:
    Curl curl_;
    Sensor sensor_;
    SensorData sensorData_;
    unsigned long long getSecondsSinceEpoch();
};

#endif
