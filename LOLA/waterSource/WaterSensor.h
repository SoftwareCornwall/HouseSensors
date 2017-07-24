#ifndef WATER_SENSOR_DEFINED
#define WATER_SENSOR_DEFINED

class WaterSensor
{
public:
    WaterSensor();
    float getRecordedWaterFlow(float timeScale);
};

void handlePin25Changed();

#endif //WATER_SENSOR_DEFINED
