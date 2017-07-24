#ifndef CURL_DEFINED
#define CURL_DEFINED

#include <string>

#include <curl/curl.h>

class Curl
{
public:
    Curl();
    bool getMACAddress(std::string& mACAddress);
    CURLcode submitSensorDataToServer(float waterFlow);
private:
    std::string mACAddress_;
    unsigned int sensorReadInterval_;
    char curlErrorBuffer_[CURL_ERROR_SIZE];
    CURLcode postDataToServer(std::string const& postFields, std::string const& serverURL);
    unsigned int getSecondsUntilNextPost();
    unsigned long long getSecondsSinceEpoch();
};

#endif
