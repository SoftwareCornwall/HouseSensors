#ifndef CURL_DEFINED
#define CURL_DEFINED

#include <string>
#include <curl/curl.h>

#include "../Sensor/Sensor.h"

class Curl
{
public:
    Curl();
    ~Curl();
    bool getMACAddress(std::string& mACAddress);
    CURLcode submitSensorDataToServer(const std::string& postData, const std::string& destination);
    CURLcode postDataToServer(std::string const& postFields, std::string const& serverURL);
    std::string getPostDataFromSensorData(const SensorData& sensorData);
private:
    std::string mACAddress_;
    unsigned long long getSecondsSinceEpoch();
};

#endif
