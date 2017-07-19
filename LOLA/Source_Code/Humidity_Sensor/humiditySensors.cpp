#include "humiditySensors.h"

using namespace std;

bool isSetup;

RTIMU *imu;
RTHumidity *humidity;

bool Setup()
{
    cout << "Setting up... ";

    ///RTIMU Setup
    if (!isSetup) // If setup hasn't already happened,
    {
        RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

        imu = RTIMU::createIMU(settings);
        humidity = RTHumidity::createHumidity(settings);

        if((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL))
        {
            cout << "Error when setting up.\nimu is null or imutype is null." << endl;
            return false;
        }

        if (!(imu->IMUInit())) // If initialisation fails.
        {
            cout << "Initialisation failed." << endl;
            return false;
        }

        cout << "Initialisation succeeded." << endl;

        if (humidity != NULL)
        {
            humidity->humidityInit();
        }

        isSetup = true;
    }
    else
    {
        cout << "Setup failed. Setup has already occured." << endl;
    }

    return true;
}

bool Cleanup()
{
    cout << "Cleaning up... ";

    curl_global_cleanup();

    cout << "Complete." << endl;
}

int main()
{
    if (Setup())
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
        Cleanup();
        exit(1);
    }




    for(;;) // Main Loop
    {

        float humidity = GetIMUHumidity();

        cout << "Sending humidity (" << humidity << ") to server (" << SERVER_URL << ")... ";

        if (CurlHumidityToServer(humidity, SERVER_URL))
        {
            cout << "Success" << endl;
        }
        else
        {
            cout << "Failure" << endl;
            break;
            // TODO: Add failure code.
        }

        std::this_thread::sleep_for(std::chrono::seconds(5 * MINUTE));
    }



    Cleanup();

    exit(0);
}

float GetIMUHumidity()
{
    if (!isSetup) return -1;

    if (imu->IMURead()) // Read data from IMU, if it succeeds...
    {
        RTIMU_DATA imuData = imu->getIMUData(); // ... get the read data.

        if (humidity != NULL)
        {
            humidity->humidityRead(imuData);
            cout << "Humidity: " << imuData.humidity << endl;

            return static_cast<float>(imuData.humidity); // returns the humidity as afloat (cast from RTFloat).
        }
    }

    return -1;
}

bool CurlHumidityToServer(float humidity, std::string serverURL)
{
    bool result = false;

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if(curl)
    {
        std::string humidityPostField = "humidityValue=" + std::to_string(humidity);

        curl_easy_setopt(curl, CURLOPT_URL, serverURL.c_str()); // Sets the destination.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, humidityPostField.c_str()); // Sets the data to be sent.

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        result = (res == CURLE_OK);
    }

    return result;
}
