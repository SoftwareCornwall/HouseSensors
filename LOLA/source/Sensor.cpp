#include "Sensor.h"
#include "StyleEscapeSequences.h"

using namespace std;


Sensor::Sensor()
{
    imu_ = unique_ptr<RTIMU>(RTIMU::createIMU(settings_.get()));
    humidity_ = unique_ptr<RTHumidity>(RTHumidity::createHumidity(settings_.get()));

    if ((imu_ == NULL) || (imu_->IMUType() == RTIMU_TYPE_NULL))
    {
        cerr << RED_FONT << "Error when setting up.\nEither there is no IMU attached or it is not supported." << DEFAULT_FONT << endl;
        throw exception();
    }

    if (!(imu_->IMUInit()))
    {
        cerr << RED_FONT << "IMU Initialisation failed." << DEFAULT_FONT << endl;
        throw exception();
    }

    cout << GREEN_FONT << "IMU Initialisation succeeded." << DEFAULT_FONT << endl;

    if (humidity_ != NULL)
    {
        humidity_->humidityInit();
    }
}



bool Sensor::getData(SensorData* sensorData)
{
    imu_->IMURead();

    if (imu_)
    {
        RTIMU_DATA imuData = imu_->getIMUData(); // ... get the read data.

        if (humidity_ != NULL)
        {
            humidity_->humidityRead(imuData);

            sensorData->humidity = static_cast<float>(imuData.humidity); // gets the humidity as afloat (cast from RTFloat).
            sensorData->temperature = static_cast<float>(imuData.temperature); // gets tempererature as a float (cast from RTFloat).
            return true;
        }
    }
    return false;
}
