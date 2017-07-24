#include <iostream>
#include <wiringPi.h>

#include "WaterSensor.h"

int interruptCounter;

WaterSensor::WaterSensor()
{
    wiringPiSetupSys();
    interruptCounter = 0;

    pinMode(25, INPUT);
    wiringPiISR(25, INT_EDGE_BOTH, handlePin25Changed);

    std::cout << "WaterSensor instance created." << std::endl;
}



float WaterSensor::getRecordedWaterFlow(float timeScale)
{
    int counter = interruptCounter;
    interruptCounter = 0;

    float waterFlow = (counter / 2200.0f / timeScale);

    std::cout << counter << " interrupts - " << (counter / timeScale) << "Hz - " << waterFlow << " litres/minute\n" << std::endl;


    return waterFlow;
}



void handlePin25Changed()
{
    interruptCounter++;
}
