#include "humiditySensors.h"

using namespace std;

struct sensorData_t
{
    unsigned long long timestamp;
    float temperature;
    float humidity;
};

std::string mACAddress;
bool isSetup;
RTIMU *imu;
RTHumidity *humidity;

char curlErrorBuffer[CURL_ERROR_SIZE];

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
    sensorData_t sensorData;

    for(;;) // Main Loop
    {

        cout << "\nNEW POST\n  Getting sensor data... ";

        if (GetSensorData(sensorData)) // Gives sensordata info from IMU, if successfull...
        {
            cout << "Success" << endl;

            SubmitDataToServer(sensorData);
        }
        else
        {
            cout << "Failure, skipping post" << endl;
        }

        cout << "END POST\nWaiting..." << endl;



        std::this_thread::sleep_for(std::chrono::seconds(3)); // Wait 5 minutes.
    }



    Cleanup();

    exit(0);
}

CURLcode SubmitDataToServer(sensorData_t sensorData)
{
    std::string postFields;
    postFields = "timestamp=" +
                  std::to_string(sensorData.timestamp) +
                  "&mac=" +
                  mACAddress +
                  "&humidityValue=" +
                  std::to_string(sensorData.humidity) +
                  "&temperatureValue=" +
                  std::to_string(sensorData.temperature);

    cout << "Posting data to server (" << SERVER_URL << ")... " << endl;
    cout <<   "  MAC Address: " << mACAddress << endl;
    cout <<   "    Timestamp: " << sensorData.timestamp << endl;
    cout <<   "     Humidity: " << sensorData.humidity << endl;
    cout <<   "  Temperature: " << sensorData.temperature << endl;
    cout <<   "       Status: ";

    CURLcode result = PostDataToServer(postFields,
                                       SERVER_URL HUMIDITY_TEMPERATURE_DIR);

    if (result == CURLE_OK)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
    }

    cout << "               Error Code: " << result << "\n               " << curlErrorBuffer << endl;

    return result;
}

bool Setup()
{
    cout << "Setting up... " << endl;

    if (!isSetup) // If setup hasn't already happened,
    {
        // MAC Setup

        if (!GetMACAddress(mACAddress))
        {
            cerr << "Failed to obtain MAC address from " << MAC_ADDRESS_FILE << ".";
            return false;
        }

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
    cout << "Cleaning up. ";

    curl_global_cleanup();

    cout << "Complete." << endl;

    return true;
}

bool GetSensorData(sensorData_t sensorData)
{
    if (!isSetup) throw "Setup not completed.";

    if (imu->IMURead()) // Read data from IMU, if it succeeds...
    {
        RTIMU_DATA imuData = imu->getIMUData(); // ... get the read data.

        if (humidity != NULL)
        {
            humidity->humidityRead(imuData);

            sensorData.humidity = static_cast<float>(imuData.humidity); // gets the humidity as afloat (cast from RTFloat).
            sensorData.temperature = static_cast<float>(imuData.temperature); // gets tempererature as a float (cast from RTFloat).
            sensorData.timestamp = GetSecondsSinceEpoch();

            return true;
        }
    }

    return false;
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

unsigned long long GetSecondsSinceEpoch()
{
    return static_cast<unsigned long long>(std::time(nullptr)); // returns Unix time as a LLU.
}

bool GetMACAddress(std::string& address)
{
    ifstream mACFile(MAC_ADDRESS_FILE);

    if (mACFile.is_open())
    {
        getline(mACFile, address);
        mACFile.close();
        return true;
    }
    else
    {
        mACFile.close();
        return false;
    }
}

