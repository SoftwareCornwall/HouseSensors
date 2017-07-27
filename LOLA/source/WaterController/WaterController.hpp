#ifndef WATER_CONTROLLER_H_DEFINED
#define WATER_CONTROLLER_H_DEFINED

void incrementInterruptCounter();

class WaterController
{
public:
    WaterController();
    ~WaterController();
    bool initialise();
    float read();
    float quietRead();
private:
    bool isInitialised_;
    long long timeAtLastRead_;
};

#endif
