#include "bme680Sensor.h"
#include "../lib/bme680.h"
void bme680Sensor::init()
{
    Serial.print(F("Connecting to BME680"));
    while (!bme.begin())
    {
        Serial.print(F("."));
        delay(500);
    }
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_8X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_0);
    bme.setPressureOversampling(BME680_OS_8X);
    bme.setGasHeater(320, 150);
    minMeasureDelay = bme.beginReading();
    Serial.println(F("[OK]"));
    
}

UnifiedSensor_t bme680Sensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    data.sensorType = S_TYPE_INVALID;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
        lastMeasurement = currentMilliseconds;
        if (bme.endReading())
        {
            data.sensorType = S_TYPE_BME680;
            data.temperature = bme.readTemperature();
            data.pressure = bme.readPressure() / 100.0;
            data.tvoc = bme.readGas();
            data.humidity = bme.readHumidity();
        }
        else
        {
            Serial.println(F("Could not read BME680"));
        }
        uint32_t next = bme.beginReading();
        minMeasureDelay = (next - currentMilliseconds);
        return data;
    }
    return data;
}
