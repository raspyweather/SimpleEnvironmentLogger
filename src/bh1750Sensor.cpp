#include "sensor.h"
#include "BH1750.h"
#include "bh1750Sensor.h"
#include <cstdint>

void bh1750Sensor::init()
{
    Serial.print(F("Connecting to BH1750"));
    while (!lightMeter.begin())
    {
        Serial.print(F("."));
        delay(500);
    }
    Serial.println(F("[OK]"));
}

UnifiedSensor_t bh1750Sensor::measureData(uint32_t milliseconds)
{
    UnifiedSensor_t data;
    data.sensorType = S_TYPE_BH1750;
    data.lightIntensity = lightMeter.readLightLevel();
    return data;
}