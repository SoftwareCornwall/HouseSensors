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

#define SERVER_URL "http://10.160.50.153/humidity_sensor.php"
#define MAC_ADDRESS_FILE "/sys/class/net/wlan0/address"

int main();

bool Setup();
bool Cleanup();
float GetIMUHumidity();
std::string GetSecondsSinceEpoch();
CURLcode PostDataToServer(std::string postFields, std::string serverURL);
bool GetMACAddress(std::string& address);

#endif
