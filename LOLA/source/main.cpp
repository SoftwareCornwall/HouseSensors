#include "Curl/Curl.hpp"
#include "Utility/Utility.hpp"
#include "IMUController/IMUController.hpp"
#include "WaterController/WaterController.hpp"

#include <iostream>
#include <signal.h>

#define SERVER_URL             "http://178.62.42.117/"
#define IMU_DATA_DESTINATION   "humidity_temperature_sensor.php"
#define WATER_DATA_DESTINATION "water_usage_sensor.php"

using namespace std;
using namespace Utility;

bool keepLooping = true;

void handleSIGINT(int param)
{
    (void)param;
    keepLooping = false;
}



void useIMUSensor(IMUController& controller, Curl& curl, const string& mACAddress)
{
    curl.initialise();
    printStyled("Controller Initialisation...", StringStyle::BOLD);

    bool success = controller.initialise();
    if (success)
    {

        while (true)
        {
            while (keepLooping && getUnixTime() % 300 != 0)
                ;

            if (!keepLooping)
                break;


            IMUReading reading = controller.read();
            cout << "Reading Details: \n    Humidity:" << reading.humidity << "\n    Temperature: " << reading.temperature << endl;

            curl.postStringTo("mac=" + mACAddress + "&timestamp=" + to_string(getUnixTime()) + "&" + serialiseIMUReading(reading), SERVER_URL IMU_DATA_DESTINATION);

            Sleep(1);
        }
    }
}



void useWaterSensor(WaterController& controller, Curl& curl, const string& mACAddress)
{
    curl.initialise();
    printStyled("Controller Initialisation...", StringStyle::BOLD);

    bool success = controller.initialise();
    if (success)
    {

        while (true)
        {
            while (keepLooping && getUnixTime() % 60 != 0)
                ;

            if (!keepLooping)
                break;


            float reading = controller.read();
            cout << "Reading Details: \n    Water Flow:" << reading << endl;

            curl.postStringTo("mac=" + mACAddress + "&timestamp=" + to_string(getUnixTime()) + "&waterValue=" + to_string(reading), SERVER_URL WATER_DATA_DESTINATION);

            Sleep(1);
        }
    }
}



int main()
{
    signal(SIGINT, handleSIGINT);

    const bool doLoopOnInvalidInput = true;
    SensorType sensorType = getSensorTypeFromUser(doLoopOnInvalidInput);

    string mACAddress = getMACAddress();
    Curl curl;

    if (sensorType == SensorType::IMU)
    {
        IMUController controller;
        useIMUSensor(controller, curl, mACAddress);
    }
    else if (sensorType == SensorType::WATER)
    {
        WaterController controller;
        useWaterSensor(controller, curl, mACAddress);
    }

    return 0;
}
