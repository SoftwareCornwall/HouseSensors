#include "humiditySensors.h"
#include "Humidity.h"
#include "Curl.h"

#include <signal.h>

#define SENSOR_READ_INTERVAL 300

using namespace std;

bool doLoop;
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

    signal(SIGINT, handleSIGINT); // Sets up Ctrl+C handler to exit main loop, not entire program.

    if(Setup())
    {
        cout << "Setup successful." << endl;
        cout << "Sensor started at " << GetSecondsSinceEpoch() << " Unix Time, waiting for " << GetSecondsUntilNextPost() << " seconds until first POST." << endl;
    }
    else
    {
        cerr << "Setup failed." << endl;

        Cleanup();
        exit(-1);
    }

    for(;;) // Main Loop
    {
        while(doLoop && (GetSecondsSinceEpoch() % SENSOR_READ_INTERVAL  != 0)); // Hangs until unix time is divisible by SENSOR_READ_INTERVAL | DoLoop eval means program will immediately stop on Ctrl+C.

        if (!doLoop) break;

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

        this_thread::sleep_for(chrono::seconds(1)); // Sleeps 1 seconds, prevents multiple posts during single seconds.
    }

    Cleanup();

    exit(0);
}

void handleSIGINT(int param)
{
    (void)param;

    cout << "\nInterrupt detected. Now exiting..." << endl;
    doLoop = false;
}

void Cleanup()
{
    cout << "Cleaning up..." << endl;

    curl_global_cleanup();

    cout << "Complete." << endl;
}

bool Setup()
{
    doLoop = true;
    return true;
}

unsigned int GetSecondsUntilNextPost()
{
    return SENSOR_READ_INTERVAL - (GetSecondsSinceEpoch() % SENSOR_READ_INTERVAL);
}

unsigned long long GetSecondsSinceEpoch()
{
    return static_cast<unsigned long long>(std::time(nullptr)); // returns Unix time as a LLU.
}
