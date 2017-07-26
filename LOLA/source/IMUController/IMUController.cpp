#include "IMUController.h"

#include "../StyleEscapeSequences.h"

#include <iostream>
#include <chrono>
#include <thread>

#define SERVER_URL                "http://raspberrypi-b.local"
#define HUMIDITY_TEMPERATURE_FILE "/humidity_temperature_sensor.php"
#define SENSOR_READ_INTERVAL      10

using namespace std;

IMUController::IMUController()
{

}



IMUController::~IMUController()
{

}




bool IMUController::setup()
{
    if (sensor_.setup())
    {
        cout << GREEN_FONT << "Setup successful." << DEFAULT_FONT << endl;
        cout << "Sensor started at " << getSecondsSinceEpoch() << " Unix Time, waiting for "
              << (SENSOR_READ_INTERVAL - (getSecondsSinceEpoch() % SENSOR_READ_INTERVAL)) // seconds until next post.
              << " seconds until first POST." << endl;

        return true;
    }
    else
    {
        cout << RED_FONT << "Setup failed." << DEFAULT_FONT << endl;
        return false;
    }
}



void IMUController::run(const bool& executionCondition)
{
    CURLcode result;

    while (true)
    {
        while (executionCondition && (getSecondsSinceEpoch() % SENSOR_READ_INTERVAL  != 0)) // Hangs until unix time is divisible by SENSOR_READ_INTERVAL
            ;

        if (!executionCondition) break;

        cout << "\nNEW POST OPERATION\033[0m \nGetting sensor data..." << endl;

        if (sensor_.getData(&sensorData_)) // Gives sensordata info from IMU, if successfull...
        {
            cout << GREEN_FONT << "Success" << DEFAULT_FONT << endl;

            cout << "Posting data to server (" << SERVER_URL HUMIDITY_TEMPERATURE_FILE << ")... " << endl;
            cout << "    Timestamp: " << getSecondsSinceEpoch() << endl;
            cout << "     Humidity: " << sensorData_.humidity << endl;
            cout << "  Temperature: " << sensorData_.temperature << endl;
            cout << "       Status: " << flush;

            result = curl_.submitSensorDataToServer(sensor_.sensorDataToString(sensorData_), SERVER_URL HUMIDITY_TEMPERATURE_FILE);

            if (result == CURLE_OK)
            {
                cout << GREEN_FONT << "POST OPERATION SUCCEEDED" << DEFAULT_FONT << endl;
            }
            else
            {
                cout << RED_FONT << "POST OPERATION FAILED" << DEFAULT_FONT << endl;
            }

        }
        else
        {
            cout << RED_FONT << "Failure, skipping post" << DEFAULT_FONT << endl;
        }

        cout << "END POST OPERATION\nWaiting " << SENSOR_READ_INTERVAL << " seconds..." << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Sleeps 1 seconds, prevents multiple posts during single seconds.
    }
}



unsigned long long IMUController::getSecondsSinceEpoch()
{
    return static_cast<unsigned long long>(std::time(nullptr)); // returns Unix time as an LLU.
}
