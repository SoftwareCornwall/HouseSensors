#ifndef IMU_CONTROLLER_H_DEFINED
#define IMU_CONTROLLER_H_DEFINED

#include <string>
#include <memory>
#include <RTIMULib.h>

struct IMUReading
{
    float temperature;
    float humidity;
};

class IMUController
{
public:
    IMUController();
    ~IMUController();
    bool initialise();
    IMUReading read();
private:
    bool isInitialised_;
    std::unique_ptr<RTIMUSettings> settings_;
    std::unique_ptr<RTIMU> imu_;
    std::unique_ptr<RTHumidity> humidity_;
};

#endif
