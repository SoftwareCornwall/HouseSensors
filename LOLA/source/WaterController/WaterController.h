#ifndef WATER_CONTROLLER_DEFINED
#define WATER_CONTROLLER_DEFINED

#include "../Curl/Curl.h"

void handlePin25Changed();

class WaterController
{
public:
    WaterController();
    bool setup();
    void run(const bool& executionCondition);
    float getRecordedWaterFlow(float timeScale);
    void incrementInterruptCounter();
private:
    Curl curl_;
    unsigned long long getSecondsSinceEpoch();
};

#endif
