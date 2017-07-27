#include "Utility.hpp"

#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>

#define MAC_ADDRESS_FILE "/sys/class/net/wlan0/address"

using namespace std;

string Utility::getMACAddress()
{
    ifstream mACFile(MAC_ADDRESS_FILE);
    string mACAddress = "";

    if (mACFile.is_open())
    {
        getline(mACFile, mACAddress);
    }

    mACFile.close();
    return mACAddress;
}



long long Utility::getUnixTime()
{
    return static_cast<long long>(std::time(nullptr)); // Gets Unix time, converts it to a long long.
}



Utility::SensorType Utility::getSensorTypeFromUser(bool loopOnInvalidInput)
{
    cout << "Enter Sensor Type: (\"imu\", \"water\")." << endl;

    string userInput;

    do // while (loopOnInvalidInput)
    {
        cout << "> " << flush;
        cin >> userInput;

        if (userInput == "imu")
        {
            cout << "Chosen sensor type: '" << userInput << "'" << endl;
            return SensorType::IMU;
        }
        else if (userInput == "water")
        {
            cout << "Chosen sensor type: '" << userInput << "'" << endl;
            return SensorType::WATER;
        }
        else
        {
            cout << "Unrecognised string." << endl;
        }
    }
    while (loopOnInvalidInput);

    return Utility::SensorType::NONE;
}



string Utility::styleString(const string& message, Utility::StringStyle style)
{
    const string styleStrings[6] =
    {
        "\033[0m",           // StringStyle::DEFAULT (Resets text to default look.)
        "\033[0;32m",        // StringStyle::GREEN
        "\033[0;31m",        // StringStyle::RED
        "\033[1m",           // StringStyle::BOLD
        "\033[0;32m\033[1m", // StringStyle::BOLD_GREEN
        "\033[0;31m\033[1m"  // StringStyle::BOLD_RED
    };

    return styleStrings[style] + message + styleStrings[0];
}



void Utility::printStyled(const string& message, Utility::StringStyle style)
{
    cout << styleString(message, style) << endl;
}


void Utility::Sleep(int seconds)
{
    this_thread::sleep_for(chrono::seconds(seconds));
}

string Utility::serialiseIMUReading(const IMUReading& reading)
{
    return ("humidityValue=" + to_string(reading.humidity) + "&temperatureValue=" + to_string(reading.temperature));
}
