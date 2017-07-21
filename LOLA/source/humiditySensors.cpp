#include "humiditySensors.h"
#include "Humidity.h"
#include "Curl.h"

using namespace std;

bool isSetup;
Humidity humidity;
Curl curl;
sensorData_t sensorData;

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

    if(Setup())
    {
        cout << "Setup successful." << endl;
    }
    else
    {
        cerr << "Setup failed." << endl;

        Cleanup();
        exit(-1);
    }

    std::string postFields;

    for(;;) // Main Loop
    {
        cout << "\nNEW POST\nGetting sensor data... " << endl;

        if (humidity.GetSensorData(&sensorData)) // Gives sensordata info from IMU, if successfull...
        {
            cout << "Success" << endl;

            curl.SubmitDataToServer(GetSecondsSinceEpoch(), sensorData);
        }
        else
        {
            cout << "Failure, skipping post" << endl;
        }

        cout << "END POST\nWaiting..." << endl;

        std::this_thread::sleep_for(std::chrono::minutes(1)); // Wait 5 minutes.
    }

    Cleanup();

    exit(0);
}

bool Setup()
{
    return true;
}

bool Cleanup()
{
    cout << "Cleaning up. ";

    curl_global_cleanup();

    cout << "Complete." << endl;

    return true;
}

unsigned long long GetSecondsSinceEpoch()
{
    return static_cast<unsigned long long>(std::time(nullptr)); // returns Unix time as a LLU.
}


