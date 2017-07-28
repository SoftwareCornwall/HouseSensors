#include "Curl.hpp"
#include "../Utility/Utility.hpp"

#include <curl/curl.h>
#include <memory>
#include <iostream>

using namespace std;

Curl::Curl()
{
    doDisplayMessages = true;
    isInitialised_ = false;
}

Curl::~Curl()
{
    Utility::printStyled("Destructing Curl Object.", Utility::StringStyle::BOLD);

    if (isInitialised_)
        curl_global_cleanup();
}

bool Curl::initialise()
{
    if (!isInitialised_)
    {
        CURLcode success = curl_global_init(CURL_GLOBAL_ALL);
        isInitialised_ = (success == CURLE_OK); //Set isInitialised_ to whether the init was successful.
    }

    return isInitialised_;
}

bool Curl::postStringTo(const string& data, const string& destination)
{
    if (!isInitialised_ || data.length() == 0 || destination.length() == 0) return false;

    if (doDisplayMessages)
        cout << "Curl | POSTING DATA:\n     | Data: " << data << "\n     | Destination: " << destination << endl;

    CURL* curl = curl_easy_init();
    CURLcode result = CURLE_FAILED_INIT;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, destination.c_str()); // Sets the destination.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str()); // Sets the data to be sent.
        result = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    if (doDisplayMessages)
        cout << "     | Result: " << result << '\n' << endl;

    return (result == CURLE_OK);
}
