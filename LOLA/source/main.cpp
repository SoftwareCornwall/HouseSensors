#include "main.hpp"
#include "Utility/Utility.hpp"

#include <iostream>
#include <signal.h>
#include <vector>

#define SERVER_URL             "http://178.62.42.117/"
#define IMU_DATA_DESTINATION   "humidity_temperature_sensor.php"
#define WATER_DATA_DESTINATION "water_usage_sensor.php"
#define UNSENT_DATA_LENGTH     128

using namespace std;
using namespace Utility;

bool keepLooping = true;
string unsentData[UNSENT_DATA_LENGTH];

void handleSIGINT(int param)
{
    (void)param;
    keepLooping = false;
}



void useIMUSensor(IMUController& controller, Curl& curl, const string& mACAddress)
{
    curl.initialise();
    printStyled("Controller Initialisation...", StringStyle::BOLD);

    bool wasInitialisationSuccessful = controller.initialise();

    int unsentDataIndex = 0;

    if (wasInitialisationSuccessful)
    {
        while (true)
        {
            while (keepLooping && (getUnixTime() % 300 != 0))
                ;

            if (!keepLooping)
                break;


            IMUReading reading = controller.read();
            cout << "UNSENTDATA[" << unsentDataIndex << "]:\n    Humidity:" << reading.humidity << "\n    Temperature: " << reading.temperature << endl;

            unsentData[unsentDataIndex] = "mac=" + mACAddress + "&timestamp=" + to_string(getUnixTime()) + "&" + serialiseIMUReading(reading);

            for (size_t i = 0; i < UNSENT_DATA_LENGTH; i++)
            {
                if (unsentData[i].length() != 0)
                {
                    bool wasPostSucessful = curl.postStringTo(unsentData[i], SERVER_URL IMU_DATA_DESTINATION);

                    if (wasPostSucessful)
                    {
                        cout << styleString("Success", StringStyle::GREEN) << endl;
                        unsentData[i] = "";
                    }
                    else
                    {
                        cout << styleString("Failure", StringStyle::RED) << endl;
                    }
                }
            }

            unsentDataIndex = (unsentDataIndex + 1) % UNSENT_DATA_LENGTH;

            Sleep(1);
        }
    }
}



void useWaterSensor(WaterController& controller, Curl& curl, const string& mACAddress)
{
    curl.initialise();
    printStyled("Controller Initialisation...", StringStyle::BOLD);

    int unsentDataIndex = 0;

    bool success = controller.initialise();
    if (success)
    {
        while (true)
        {
            while (keepLooping && (getUnixTime() % 60 != 0))
                ;

            if (!keepLooping)
                break;


            float reading = controller.read();
            cout << "Reading Details:\n     Water Flow: " << reading << endl;

            unsentData[unsentDataIndex] = ("mac=" + mACAddress + "&timestamp=" + to_string(getUnixTime()) + "&waterValue=" + to_string(reading), SERVER_URL WATER_DATA_DESTINATION);

            for (size_t i = 0; i < UNSENT_DATA_LENGTH; i++)
            {
                if (unsentData[i].length() != 0)
                {
                    bool wasPostSucessful = curl.postStringTo(unsentData[i], SERVER_URL IMU_DATA_DESTINATION);

                    if (wasPostSucessful)
                    {
                        cout << styleString("Success", StringStyle::GREEN) << endl;
                        unsentData[i] = "";
                    }
                    else
                    {
                        cout << styleString("Failure", StringStyle::RED) << endl;
                    }
                }
            }

            unsentDataIndex = (unsentDataIndex + 1) % UNSENT_DATA_LENGTH;

            Sleep(1);
        }
    }
}



int main()
{
    const bool doLoopOnInvalidInput = true;
    SensorType sensorType = getSensorTypeFromUser(doLoopOnInvalidInput);

    signal(SIGINT, handleSIGINT);

    string mACAddress = getMACAddress();
    Curl curl;
    curl.doDisplayMessages = false;

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
