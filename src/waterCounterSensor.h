
#include "sensor.h"
#include "unifiedSensor.h"
#define WATERCOUNTERSENSORPIN D5

class waterCounterSensor : public sensor
{
private:
    uint32_t lastImpulse = 0;
    uint32_t minDelay = 200;
    bool previousState = false;
    
    int count = 0;
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 30000;
public:
    waterCounterSensor() = default;
    ~waterCounterSensor() = default;
    void init();
    void resetCount();
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
};
