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



using namespace std;

struct sensorData_t;

int main();

bool Setup();
bool Cleanup();
unsigned long long GetSecondsSinceEpoch();
bool GetMACAddress(std::string& address);

#endif
