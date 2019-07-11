#include "sds011Sensor.h"
#define SDS011_TX D0
#define SDS011_RX D5
#define HEATDELAY 30000
#define MEASUREDELAY 150000
void sds011Sensor::init()
{
    Serial.println("Connecting to SDS011");
    sds.begin(SDS011_RX, SDS011_TX);
    float PM2_5, PM10;
    sds.read(&PM2_5, &PM10);
    Serial.printf("SDS011 Test %fPM2.5 %fPM10\n", PM2_5, PM10);
    sds.sleep();
    minMeasureDelay = 1000;
}

UnifiedSensor_t sds011Sensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    data.sensorType = S_TYPE_INVALID;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
        lastMeasurement = currentMilliseconds;
        if (isHeated)
        {
            Serial.println("Measuring SDS ");
            data.sensorType = S_TYPE_SDS011;
            sds.read(&data.PM2_5, &data.PM10);
            if (isnan(data.PM2_5) || isnan(data.PM10))
            {
                Serial.println("No Data available, retry.");
                minMeasureDelay = 1000;
                return data;
            }
            sds.sleep();
            isHeated = false;
            minMeasureDelay = MEASUREDELAY;
            return data;
        }
        else
        {
            Serial.println("heating up SDS");
            minMeasureDelay = HEATDELAY;
            isHeated = true;
            sds.wakeup();
        }
    }
    return data;
}
