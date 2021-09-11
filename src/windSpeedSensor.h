#include "sensor.h"
#include <cstdint>

class windSpeedSensor : public sensor
{
private:
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 30000;

public:
    windSpeedSensor() = default;
    ~windSpeedSensor() = default;
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
    void init();
};
