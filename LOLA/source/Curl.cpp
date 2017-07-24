#include "Curl.h"
#include <iostream>
#include <fstream>
#include <exception>

#define SERVER_URL "http://raspberrypi-b.local"
#define HUMIDITY_TEMPERATURE_DIR "/humidity_temperature_sensor.php"
#define MAC_ADDRESS_FILE "/sys/class/net/wlan0/address"

using namespace std;

Curl::Curl()
{
    if (!GetMACAddress(mACAddress))
    {
        cerr << "Failed to obtain MAC address from " << MAC_ADDRESS_FILE << ".";
        throw exception();
    }
}

CURLcode Curl::SubmitDataToServer(unsigned long long secondsSinceEpoch, const sensorData_t &sensorData)
{
    string postFields = "timestamp=" +
                         std::to_string(secondsSinceEpoch) +
                         "&mac=" +
                         mACAddress +
                         "&humidityValue=" +
                         std::to_string(sensorData.humidity) +
                         "&temperatureValue=" +
                         std::to_string(sensorData.temperature);

    cout << "Posting data to server (" << SERVER_URL << ")... " << endl;
    cout <<   "  MAC Address: " << mACAddress << endl;
    cout <<   "    Timestamp: " << secondsSinceEpoch << endl;
    cout <<   "     Humidity: " << sensorData.humidity << endl;
    cout <<   "  Temperature: " << sensorData.temperature << endl;
    cout <<   "       Status: " << flush;

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

CURLcode Curl::PostDataToServer(string postFields, string serverURL)
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

bool Curl::GetMACAddress(string& address)
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
