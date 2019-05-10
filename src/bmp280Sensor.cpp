#define bmpAddr 0x76
#include "sensor.h"
#include "bmp280Sensor.h"
#include <cstdint>
#include <Adafruit_BMP280.h>

void bmp280Sensor::init()
{
    Serial.print(F("Connecting to BMP280"));
    while (!bmp.begin(bmpAddr))
    {
        Serial.print(F("."));
        delay(500);
    }
    Serial.println(F("[OK]"));
}

UnifiedSensor_t bmp280Sensor::measureData(uint32_t milliseconds)
{
    UnifiedSensor_t data;
    data.sensorType = S_TYPE_BMP280;
    data.temperature = bmp.readTemperature();
    data.pressure = bmp.readPressure() / 100;
    return data;
}
float bmp280Sensor::getTemp()
{
    return bmp.readTemperature();
}