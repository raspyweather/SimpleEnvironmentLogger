#include "sensor.h"
#include "unifiedSensor.h"
#include <SDS011.h>

class sds011Sensor : public sensor
{
private:
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 0;
    SDS011 sds;
public:
    sds011Sensor() = default;
    ~sds011Sensor() = default;
    void init();
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
};
