#define bmeAddr 0x76
#include "sensor.h"
#include "bme280Sensor.h"
#include <cstdint>
#include <Adafruit_BME280.h>

void bme280Sensor::init()
{
    Serial.print(F("Connecting to BME280"));
    while (!bme.begin(bmeAddr))
    {
        Serial.print(F("."));
        delay(500);
    }
    Serial.println(F("[OK]"));
}

UnifiedSensor_t bme280Sensor::measureData(uint32_t milliseconds)
{
    UnifiedSensor_t data;
    data.sensorType = S_TYPE_BME280;
    data.temperature = bme.readTemperature();
    data.humidity = bme.readHumidity();
    data.pressure = bme.readPressure() / 100;
    return data;
}
float bme280Sensor::getTemp()
{
    return bme.readTemperature();
}
float bme280Sensor::getHumidity()
{
    return bme.readHumidity();
}