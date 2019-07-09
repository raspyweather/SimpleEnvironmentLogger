#include "sensor.h"
#include "DHT.h"
#include <cstdint>

class wifiSensor : public sensor
{
private:
    DHT dht;
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 0;

public:
    wifiSensor() = default;
    ~wifiSensor() = default;
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
    void init();
};
