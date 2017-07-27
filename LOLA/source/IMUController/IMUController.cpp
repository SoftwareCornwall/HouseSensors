#include "IMUController.hpp"
#include "../Utility/Utility.hpp"

#include <iostream>

using namespace std;

IMUController::IMUController()
{
    isInitialised_ = false;
}



IMUController::~IMUController()
{
    Utility::printStyled("~IMUController() called. Destructing...", Utility::StringStyle::BOLD);
}



bool IMUController::initialise()
{
    settings_ = unique_ptr<RTIMUSettings>(new RTIMUSettings("RTIMULib"));
    imu_ = unique_ptr<RTIMU>(RTIMU::createIMU(settings_.get()));
    humidity_ = unique_ptr<RTHumidity>(RTHumidity::createHumidity(settings_.get()));

    if ((imu_ == NULL) || (imu_->IMUType() == RTIMU_TYPE_NULL))
    {
        cerr << "IMUController | " << Utility::styleString("Error when setting up.              | \nEither there is no IMU attached or it is not supported.", Utility::StringStyle::RED) << '\n' << endl;
        return false;
    }
    else
    {
        if (!(imu_->IMUInit()))
        {
            cerr << "IMUController | " << Utility::styleString("IMU Initialisation failed.", Utility::StringStyle::RED) << '\n' << endl;
            return false;
        }
        else
        {
            cout << "IMUController | " << Utility::styleString("IMU Initialisation succeeded.", Utility::StringStyle::GREEN) << '\n' << endl;

            if (humidity_ != NULL)
            {
                humidity_->humidityInit();
            }

            isInitialised_ = true;
            return true;
        }
    }
}



IMUReading IMUController::read()
{
    IMUReading reading = IMUReading{ -1, -1 };

    if (isInitialised_)
    {
        imu_->IMURead();

        if (imu_ && humidity_ != NULL)
        {
            RTIMU_DATA imuData = imu_->getIMUData();
            humidity_->humidityRead(imuData);

            reading.humidity = static_cast<float>(imuData.humidity); // gets the humidity as afloat (cast from RTFloat).
            reading.temperature = static_cast<float>(imuData.temperature); // gets tempererature as a float (cast from RTFloat).
        }
    }

    return reading;
}
