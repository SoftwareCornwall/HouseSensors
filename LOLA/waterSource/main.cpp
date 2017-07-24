#include <thread>
#include <chrono>
#include <iostream>

#include "WaterSensor.h"
#include "Curl.h"

using namespace std;

void sleep(int seconds)
{
    this_thread::sleep_for(chrono::seconds(seconds));
}



int main() // 2200 pulses = 1 litre = 0.001 m^3
{
    WaterSensor sensor;
    Curl curl;

    while (true)
    {
        sleep(60);
        curl.submitSensorDataToServer(sensor.getRecordedWaterFlow(60.0f));
    }
}
