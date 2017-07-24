#ifndef HUMIDITYSENSORS_DEFINED
#define HUMIDITYSENSORS_DEFINED

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <thread>

#include <RTIMULib.h>

struct sensorData_t;

int main();
void handleSIGINT(int param);
void cleanup();
bool setup();
unsigned int getSecondsUntilNextPost();
unsigned long long getSecondsSinceEpoch();

#endif
