#include <signal.h>

#include "humiditySensors.h"
#include "Sensor.h"
#include "Curl.h"

#include "StyleEscapeSequences.h"

#define SENSOR_READ_INTERVAL 10

using namespace std;

bool isLooping;
bool isSetup;
Sensor sensor;
Curl curl;
SensorData sensorData;

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

    if (setup())
    {
        cout << GREEN_FONT << "Setup successful." << DEFAULT_FONT << endl;
        cout << "Sensor started at " << getSecondsSinceEpoch() << " Unix Time, waiting for " << getSecondsUntilNextPost() << " seconds until first POST." << endl;
    }
    else
    {
        cerr << "Setup failed." << endl;

        cleanup();
        exit(-1);
    }

    while (true) // Main Loop
    {
        while (isLooping && (getSecondsSinceEpoch() % SENSOR_READ_INTERVAL  != 0)) // Hangs until unix time is divisible by SENSOR_READ_INTERVAL | DoLoop eval means program will immediately stop on Ctrl+C.
            ;


        if (!isLooping) break;

        cout << "\nNEW POST OPERATION\033[0m \nGetting sensor data..." << endl;

        if (sensor.getData(&sensorData)) // Gives sensordata info from IMU, if successfull...
        {
            cout << GREEN_FONT << "Success" << DEFAULT_FONT << endl;

            curl.submitSensorDataToServer(getSecondsSinceEpoch(), sensorData);
        }
        else
        {
            cout << RED_FONT << "Failure, skipping post" << DEFAULT_FONT << endl;
        }

        cout << "END POST OPERATION\nWaiting " << SENSOR_READ_INTERVAL << " seconds..." << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Sleeps 1 seconds, prevents multiple posts during single seconds.
    }

    cleanup();

    exit(0);
}



void handleSIGINT(int param)
{
    (void)param; //Supresses the "unused variable" error. param is needed for the SIGINT handling to work.

    cout << "\nInterrupt detected. Now exiting..." << endl;
    isLooping = false;
}



void cleanup()
{
    cout << "Cleaning up..." << endl;

    curl_global_cleanup();

    cout << "Complete." << endl;
}



bool setup()
{
    isLooping = true;
    return true;
}



unsigned int getSecondsUntilNextPost()
{
    return SENSOR_READ_INTERVAL - (getSecondsSinceEpoch() % SENSOR_READ_INTERVAL);
}



unsigned long long getSecondsSinceEpoch()
{
    return static_cast<unsigned long long>(std::time(nullptr)); // returns Unix time as an LLU.
}
