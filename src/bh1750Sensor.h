
#include "sensor.h"
#include "unifiedSensor.h"
#include <BH1750.h>

class bh1750Sensor : public sensor
{
private:
    BH1750 lightMeter= BH1750(0x23);
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 0;
public:
    bh1750Sensor() = default;
    ~bh1750Sensor() = default;
    void init();
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
};
