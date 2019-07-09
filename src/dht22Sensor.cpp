#include "dht22Sensor.h"
void dht22Sensor::init()
{
    dht.setup(D3, DHT::DHT22);
    minMeasureDelay = dht.getMinimumSamplingPeriod();
}

UnifiedSensor_t dht22Sensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
        lastMeasurement = currentMilliseconds;
        data.sensorType = S_TYPE_DHT22;
        data.humidity = dht.getHumidity();
        data.temperature = dht.getTemperature();
        return data;
    }
    data.sensorType = S_TYPE_INVALID;
    return data;
}