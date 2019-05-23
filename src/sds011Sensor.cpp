#include "sds011Sensor.h"
#define SDS011_TX D7
#define SDS011_RX D8
void sds011Sensor::init()
{
    Serial.println("Connecting to SDS011");
    sds.begin(SDS011_RX, SDS011_TX);
    sds.sleep();
    minMeasureDelay = 150000;
}

UnifiedSensor_t sds011Sensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
        lastMeasurement = currentMilliseconds;
        data.sensorType = S_TYPE_SDS011;
        sds.wakeup();

        sds.read(&data.PM2_5, &data.PM10);
        sds.sleep();
        return data;
    }
    data.sensorType = S_TYPE_INVALID;
    return data;
}
