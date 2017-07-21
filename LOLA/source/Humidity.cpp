#include "Humidity.h"

using namespace std;

Humidity::Humidity()
{
    settings = unique_ptr<RTIMUSettings>(new RTIMUSettings("RTIMULib"));

    imu = RTIMU::createIMU(settings.get());
    humidity = RTHumidity::createHumidity(settings.get());

    if((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL))
    {
        cerr << "Error when setting up.\n  imu is null or imutype is null." << endl;
        throw exception();
    }

    if (!(imu->IMUInit()))
    {
        cerr << "IMU Initialisation failed." << endl;
        throw exception();
    }

    cout << "IMU Initialisation succeeded." << endl;

    if (humidity != NULL)
    {
        humidity->humidityInit();
    }
}

bool Humidity::GetSensorData(sensorData_t* sensorData)
{
    if (imu->IMURead()) // Read data from IMU, if it succeeds...
    {
        RTIMU_DATA imuData = imu->getIMUData(); // ... get the read data.

        if (humidity != NULL)
        {
            humidity->humidityRead(imuData);

            sensorData->humidity = static_cast<float>(imuData.humidity); // gets the humidity as afloat (cast from RTFloat).
            sensorData->temperature = static_cast<float>(imuData.temperature); // gets tempererature as a float (cast from RTFloat).
            return true;
        }
    }
    return false;
}
