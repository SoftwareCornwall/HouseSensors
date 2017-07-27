#ifndef CURL_H_DEFINED
#define CURL_H_DEFINED

#include <string>

class Curl
{
public:
    Curl();
    ~Curl();
    bool doDisplayMessages;
    bool initialise();
    bool postStringTo(const std::string& data, const std::string& destination);
private:
    bool isInitialised_;
};

#endif
