#include "humiditySensors.h"

using namespace std;

bool isSetup;

RTIMU *imu;
RTHumidity *humidity;

bool setup()
{
    ///RTIMU Setup

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
    return true;
}

int main()
{
    cout << "Setting up... ";

    if (setup())
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
        exit(1);
    }

    float humidity = GetIMUHumidity();

    cout << "Sending humidity (" << humidity << ") to server (" << SERVER_URL << ")... ";

    if (CurlHumidityToServer(humidity, SERVER_URL))
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
        exit(1);
    }

    exit(0);
}

float GetIMUHumidity()
{
    if (!isSetup) return false;

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

    return 0;
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

    curl_global_cleanup();

    return result;
}
