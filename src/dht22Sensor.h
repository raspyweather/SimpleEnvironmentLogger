#define DHTPIN D5
#include "sensor.h"
#include "DHT.h"
#include <cstdint>

class dht22Sensor : public sensor
{
private:
    DHT dht;
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 0;

public:
    dht22Sensor() = default;
    ~dht22Sensor() = default;
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
    void init();
};
