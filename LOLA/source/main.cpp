#include "IMUController/IMUController.h"
#include "WaterController/WaterController.h"
#include "Curl/Curl.h"
#include "StyleEscapeSequences.h"

#include <signal.h>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <chrono>
#include <RTIMULib.h>


using namespace std;

bool doAllowExecution = true;

enum SensorType
{
    IMU,
    Water
};

SensorType GetSensorType()
{
    cout << "Enter Sensor Type: (\"imu\", \"water\")." << endl;

    string userInput;

    while (true)
    {
        cout << "> " << flush;
        cin >> userInput;

        if (userInput == "imu")
        {
            cout << "Chosen sensor type: '" << userInput << "'" << endl;
            return SensorType::IMU;
        }
        else if (userInput == "water")
        {
            cout << "Chosen sensor type: '" << userInput << "'" << endl;
            return SensorType::Water;
        }
        else
        {
            cout << "Unrecognised string. Either enter \"imu\" or \"water\"." << endl;
        }
    }
}



void handleSIGINT(int param)
{
    (void)param; //Supresses the "unused variable" error. param is needed for the SIGINT handling to work.

    doAllowExecution = false;

    cout << "\nInterrupt detected. Now exiting..." << endl;
}



void cleanup()
{
    cout << "Cleaning up..." << endl;

    curl_global_cleanup();

    cout << "Complete." << endl;
}



int main()
{
    cout << R"(
 _   _                      _____
| | | |                    /  ___|
| |_| | ___  _   _ ___  ___\ `--.  ___ _ __  ___  ___  _ __
|  _  |/ _ \| | | / __|/ _ \`--. \/ _ \ '_ \/ __|/ _ \| '__|
| | | | (_) | |_| \__ \  __/\__/ /  __/ | | \__ \ (_) | |
\_| |_/\___/ \__,_|___/\___\____/ \___|_| |_|___/\___/|_|
    ___     _____ _       _____
   / / |   |  _  | |     / _ \ \
  | || |   | | | | |    / /_\ \ |
  | || |   | | | | |    |  _  | |
  | || |___\ \_/ / |____| | | | |
  | |\_____/\___/\_____/\_| |_/ |
   \_\                       /_/
)" << endl;

    signal(SIGINT, handleSIGINT); // Sets up Ctrl+C handler to exit main loop, not entire program.

    SensorType sensorType = GetSensorType();

    IMUController iMUController;
    WaterController waterController;

    switch (sensorType)
    {
        case SensorType::IMU:
            if (iMUController.setup())
            {
                iMUController.run(doAllowExecution);
            }
            break;
        case SensorType::Water:
            if (waterController.setup())
            {
                waterController.run(doAllowExecution);
            }
            break;
        default:
            throw exception();
    }

    cleanup();
    exit(0);
}
