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
void handleSIGINT(int param);
void Cleanup();
bool Setup();
unsigned int GetSecondsUntilNextPost();
unsigned long long GetSecondsSinceEpoch();

#endif
