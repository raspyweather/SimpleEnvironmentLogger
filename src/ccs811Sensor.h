
#include "sensor.h"
#include "Adafruit_CCS811.h"
#define ccsAddr 0x5A
class ccs811Sensor : public sensor
{
private:
    Adafruit_CCS811 ccs;
    float (*getTemp)();
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 250;

public:
    ccs811Sensor(float (*getTempF)())
    {
        getTemp = getTempF;
    }
    ~ccs811Sensor() = default;
    void init();
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
    void calibrate();
};
