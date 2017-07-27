#ifndef UTILITY_H_DEFINED
#define UTILITY_H_DEFINED

#include "../IMUController/IMUController.hpp"

#include <string>

namespace Utility
{
    enum SensorType
    {
        NONE,
        WATER,
        IMU
    };

    enum StringStyle
    {
        DEFUALT,
        GREEN,
        RED,
        BOLD,
        BOLD_GREEN,
        BOLD_RED,
    };

    std::string styleString(const std::string& message, StringStyle style);
    void printStyled(const std::string& message, StringStyle style);
    SensorType getSensorTypeFromUser(bool loopOnInvalidInput);
    std::string getMACAddress();
    long long getUnixTime();
    void Sleep(int seconds);
    std::string serialiseIMUReading(const IMUReading& reading);
}

#endif
