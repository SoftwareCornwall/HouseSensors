#ifndef HUMIDITYSENSORS_DEFINED
#define HUMIDITYSENSORS_DEFINED

#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>

#include "RTIMULib.h"

#define SERVER_URL "http://10.160.50.153/humidity_sensor.php"
#define MINUTE 60


int main();

bool Setup();
bool Cleanup();
float GetIMUHumidity();
bool CurlHumidityToServer(float humidity, std::string serverURL);

#endif
