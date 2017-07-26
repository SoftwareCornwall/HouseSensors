#include "WaterController.h"

#include "../StyleEscapeSequences.h"

#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include <thread>

#define SERVER_URL                "http://raspberrypi-b.local"
#define WATER_FILE               "/water_usage_sensor.php"
#define SENSOR_READ_INTERVAL     10

using namespace std;


unsigned int interruptCounter;

WaterController::WaterController()
{

}



bool WaterController::setup()
{
    wiringPiSetupSys();
    interruptCounter = 0;

    pinMode(25, INPUT);
    wiringPiISR(25, INT_EDGE_BOTH, handlePin25Changed);

    std::cout << "WaterSensor instance created." << std::endl;

    return true;
}



void WaterController::run(const bool& executionCondition)
{
    float waterFlow;
    CURLcode result;

    while (true)
    {
        while (executionCondition && (getSecondsSinceEpoch() % SENSOR_READ_INTERVAL  != 0)) // Hangs until unix time is divisible by SENSOR_READ_INTERVAL
            ;

        if (!executionCondition) break;

        cout << "\nNEW POST OPERATION\033[0m \nGetting sensor data..." << endl;
        waterFlow = getRecordedWaterFlow(SENSOR_READ_INTERVAL);


        cout << "Posting data to server (" << SERVER_URL WATER_FILE << ")... " << endl;
        cout << "    Timestamp: " << getSecondsSinceEpoch() << endl;
        cout << "   Water Flow: " << waterFlow << endl;
        cout << "       Status: " << flush;

        result = curl_.submitSensorDataToServer("waterValue=" + std::to_string(waterFlow), SERVER_URL WATER_FILE);

        if (result == CURLE_OK)
        {
            cout << GREEN_FONT << "POST OPERATION SUCCEEDED" << DEFAULT_FONT << endl;
        }
        else
        {
            cout << RED_FONT << "POST OPERATION FAILED" << DEFAULT_FONT << endl;
        }

        cout << "END POST OPERATION\nWaiting " << SENSOR_READ_INTERVAL << " seconds..." << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Sleeps 1 seconds, prevents multiple posts during single seconds.
    }
}



float WaterController::getRecordedWaterFlow(float timeScale)
{
    unsigned int counter = interruptCounter;
    interruptCounter = 0;

    float waterFlow = (counter / 2200.0f / timeScale);

    std::cout << BOLD_FONT << "Flow Data: " << DEFAULT_FONT << counter << " interrupts - " << (counter / timeScale) << "Hz - " << waterFlow << " litres/minute\n" << std::endl;

    return waterFlow;
}


void handlePin25Changed()
{
    interruptCounter++;
}



unsigned long long WaterController::getSecondsSinceEpoch()
{
    return static_cast<unsigned long long>(std::time(nullptr)); // returns Unix time as an LLU.
}
