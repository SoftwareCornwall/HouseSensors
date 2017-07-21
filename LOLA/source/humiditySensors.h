#ifndef HUMIDITYSENSORS_DEFINED
#define HUMIDITYSENSORS_DEFINED

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <RTIMULib.h>
#include <memory>

struct sensorData_t;

int main();

bool Setup();
bool Cleanup();
bool GetMACAddress(std::string& address);
unsigned int GetSecondsUntilNextPost();
unsigned long long GetSecondsSinceEpoch();

#endif
