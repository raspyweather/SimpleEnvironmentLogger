#include "sensor.h"
#include "unifiedSensor.h"
#include "Adafruit_BME280.h"

class bme280Sensor : public sensor
{
private:
    Adafruit_BME280 bme;
    float lastTemp;
    float lastHumidity;
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 0;
public:
    bme280Sensor() = default;
    ~bme280Sensor() = default;
    void init();
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
    float getTemp();
    float getHumidity();
};
