
#include "sensor.h"
#include "unifiedSensor.h"
#include "Adafruit_BME680.h"

class bme680Sensor : public sensor
{
private:
    Adafruit_BME680 bme;
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 0;
public:
    bme680Sensor() = default;
    ~bme680Sensor() = default;
    void init();
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
};
