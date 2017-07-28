#ifndef MAIN_H_DEFINED
#define MAIN_H_DEFINED

#include "Curl/Curl.hpp"
#include "IMUController/IMUController.hpp"
#include "WaterController/WaterController.hpp"

#include <string>

void handleSIGINT(int param);
void useIMUSensor(IMUController& controller, Curl& curl, const std::string& mACAddress);
void useWaterSensor(WaterController& controller, Curl& curl, const std::string& mACAddress);
int main();

#endif
