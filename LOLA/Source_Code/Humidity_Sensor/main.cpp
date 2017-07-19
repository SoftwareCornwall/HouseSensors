#include <stdio.h>
#include <string>
#include <iostream>

#include "RTIMULib.h"

using namespace std;



int main()
{
    float humidity = GetIMUHumidity();
}

float GetIMUHumidity()
{
    RTIMUSettings *settings = new RTIMUSettings("RTIMULib");
    RTIMU *imu = RTIMU::createIMU(settings);
    RTHumidity *humidity = RTHumidity::createHumidity(settings);

    if((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL))
    {
        cout << "Error when setting up.\nimu is null or imutype is null." << endl;
        return 0;
    }

    if (!(imu->IMUInit())) // If initialisation fails.
    {
        cout << "Initialisation failed." << endl;
        return 0;
    }

    cout << "Initialisation succeeded." << endl;

    if (humidity != NULL)
    {
        humidity->humidityInit();
    }

    if (imu->IMURead()) // Read data from IMU, if it succeeds...
    {
        RTIMU_DATA imuData = imu->getIMUData(); // ... get the read data.

        if (humidity != NULL)
        {
            humidity->humidityRead(imuData);
            cout << "Humidity: " << imuData.humidity << endl;

            return static_cast<float>(imuData.humidity);
        }
    }

    return 0;
}
