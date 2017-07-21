#ifndef HUMIDITYSENSORS_DEFINED
#define HUMIDITYSENSORS_DEFINED

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>
#include <RTIMULib.h>
#include <memory>

#define SERVER_URL "http://raspberrypi-b.local"
#define HUMIDITY_TEMPERATURE_DIR "/humidity_temperature_sensor.php"
#define MAC_ADDRESS_FILE "/sys/class/net/wlan0/address"

using namespace std;

struct sensorData_t;

int main();

CURLcode SubmitDataToServer();

bool Setup();
bool Cleanup();
unsigned long long GetSecondsSinceEpoch();
CURLcode PostDataToServer(std::string postFields, std::string serverURL);
bool GetMACAddress(std::string& address);

#endif
