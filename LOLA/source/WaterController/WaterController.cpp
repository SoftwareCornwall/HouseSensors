#include "WaterController.hpp"
#include "../Utility/Utility.hpp"

#include <wiringPi.h>

int interruptCounter;

WaterController::WaterController()
{
    isInitialised_ = false;
    timeAtLastRead_ = 0;
}



WaterController::~WaterController()
{
    Utility::printStyled("Destructing WaterController Object", Utility::StringStyle::BOLD);
}

bool WaterController::initialise()
{
    if (!isInitialised_)
    {
        interruptCounter = 0;

        wiringPiSetupSys();
        pinMode(25, INPUT);
        wiringPiISR(25, INT_EDGE_BOTH, incrementInterruptCounter);
        timeAtLastRead_ = Utility::getUnixTime();

        isInitialised_ = true;
    }

    return isInitialised_;
}



float WaterController::read()
{
    if (!isInitialised_) return -1;

    float readValue = quietRead();
    timeAtLastRead_ = Utility::getUnixTime();
    interruptCounter = 0;

    return readValue;
}



float WaterController::quietRead()
{
    if (!isInitialised_) return -1;

    return interruptCounter / 2200.0f / (Utility::getUnixTime() - timeAtLastRead_);
}



void incrementInterruptCounter()
{
    interruptCounter++;
}