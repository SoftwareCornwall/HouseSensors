#include "humiditySensors.h"

using namespace std;

bool isSetup;
RTIMU *imu;
RTHumidity *humidity;
char curlErrorBuffer[CURL_ERROR_SIZE];

int main()
{
    if(Setup())
    {
        cout << "Setup successful." << endl;
    }
    else
    {
        cerr << "Setup failed. Exiting..." << endl;

        Cleanup();
        exit(1);
    }



    std::string postFields;
    CURLcode result;

    for(;;) // Main Loop
    {
        float humidity = GetIMUHumidity();

        postFields = "timestamp=" + GetSecondsSinceEpoch() + "&humidityValue=" + std::to_string(humidity);

        cout << "Posting data (" << postFields << ") to server (" << SERVER_URL << ")... ";

        result = PostDataToServer(postFields, SERVER_URL);

        if(result == CURLE_OK)
        {
            cout << "Success" << endl;
        }
        else
        {
            cerr << "Failure:\nError Code: " << result << "\n" << curlErrorBuffer << endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait 5 minutes.
    }



    Cleanup();

    exit(0);
}

bool Setup()
{
    cout << "Setting up... " << endl;

    if (!isSetup) // If setup hasn't already happened,
    {
        // RTIMU Setup

        RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

        imu = RTIMU::createIMU(settings);
        humidity = RTHumidity::createHumidity(settings);

        if((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL))
        {
            cerr << "Error when setting up.\n  imu is null or imutype is null." << endl;
            return false;
        }

        if (!(imu->IMUInit()))
        {
            cerr << "IMU Initialisation failed." << endl;
            return false;
        }

        cout << "IMU Initialisation succeeded." << endl;

        if (humidity != NULL)
        {
            humidity->humidityInit();
        }

        isSetup = true;



        // Curl Setup

    }
    else
    {
        cerr << "Cannot set up, setup has already occured." << endl;
    }

    return true;
}

bool Cleanup()
{
    cout << "Cleaning up... ";

    curl_global_cleanup();

    cout << "Complete." << endl;

    return true;
}

float GetIMUHumidity()
{
    if (!isSetup) throw "Setup not completed.";

    if (imu->IMURead()) // Read data from IMU, if it succeeds...
    {
        RTIMU_DATA imuData = imu->getIMUData(); // ... get the read data.

        if (humidity != NULL)
        {
            humidity->humidityRead(imuData);
            return static_cast<float>(imuData.humidity); // returns the humidity as afloat (cast from RTFloat).
        }
    }

    return -1;
}

CURLcode PostDataToServer(std::string postFields, std::string serverURL)
{
    CURL *curl;
    CURLcode result = CURLE_FAILED_INIT;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, serverURL.c_str()); // Sets the destination.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str()); // Sets the data to be sent.
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlErrorBuffer); // Sets curlErrorBuffer to the curl's error message.
        result = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    return result;
}

std::string GetSecondsSinceEpoch()
{
    std::time_t time = std::time(nullptr);
    return std::to_string(static_cast<unsigned int>(time));
}
