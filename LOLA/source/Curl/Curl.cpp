#include "Curl.h"

#include "../StyleEscapeSequences.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <chrono>

#define MAC_ADDRESS_FILE "/sys/class/net/wlan0/address"

using namespace std;

Curl::Curl()
{
    if (!getMACAddress(mACAddress_)) // If the program cannot get the MAC Address.
    {
        cerr << "Failed to obtain MAC address from " << MAC_ADDRESS_FILE << ".";
        throw exception();
    }
}



Curl::~Curl()
{
    curl_global_cleanup();
}



CURLcode Curl::submitSensorDataToServer(const string& postData, const string& destination)
{
    string postFields = postData +
                         "&timestamp=" +
                         std::to_string(getSecondsSinceEpoch()) +
                         "&mac=" +
                         mACAddress_;

    CURLcode result = postDataToServer(postFields, destination);

    if (result == CURLE_OK)
    {
        cout << GREEN_FONT << "Success" << DEFAULT_FONT << endl;
    }
    else
    {
        cout << RED_FONT << "Failure" << DEFAULT_FONT << endl;
    }

    cout << "               Error Code: " << result << endl;

    return result;
}



CURLcode Curl::postDataToServer(string const& postFields, string const& serverURL)
{
    if (postFields.length() == 0)
        return CURLE_FAILED_INIT;

    CURL* curl;
    CURLcode result = CURLE_FAILED_INIT;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, serverURL.c_str()); // Sets the destination.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str()); // Sets the data to be sent.
        result = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    return result;
}



bool Curl::getMACAddress(string& mACAddress)
{
    ifstream mACFile(MAC_ADDRESS_FILE);

    if (mACFile.is_open())
    {
        getline(mACFile, mACAddress);
        mACFile.close();
        return true;
    }
    else
    {
        mACFile.close();
        return false;
    }
}



unsigned long long Curl::getSecondsSinceEpoch()
{
    return static_cast<unsigned long long>(std::time(nullptr)); // returns Unix time as an LLU.
}
