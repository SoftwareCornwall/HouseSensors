#ifndef CURL_DEFINED
#define CURL_DEFINED

#include <curl/curl.h>
#include <string>

#include "Humidity.h"

class Curl
{
public:
    Curl();
    bool GetMACAddress(std::string& address);
    CURLcode SubmitDataToServer(unsigned long long secondsSinceEpoch, const sensorData_t &sensorData);
private:
    std::string mACAddress;
    char curlErrorBuffer[CURL_ERROR_SIZE];
    CURLcode PostDataToServer(std::string postFields, std::string serverURL);

};


#endif
