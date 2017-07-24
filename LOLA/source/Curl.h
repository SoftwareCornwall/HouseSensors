#ifndef CURL_DEFINED
#define CURL_DEFINED

#include <string>

#include <curl/curl.h>

#include "Sensor.h"

class Curl
{
public:
    Curl();
    bool getMACAddress(std::string& mACAddress);
    CURLcode submitSensorDataToServer(unsigned long long secondsSinceEpoch, const SensorData& sensorData);
private:
    std::string mACAddress_;
    char curlErrorBuffer_[CURL_ERROR_SIZE];
    CURLcode postDataToServer(std::string const& postFields, std::string const& serverURL);
};

#endif
