#include "ds18b20Sensor.h"

void ds18b20Sensor::init()
{
    sensors.begin();
    Serial.print(F("Found"));
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(F(" devices."));
    // sensors.setResolution(12);
    // sensors.setWaitForConversion(false);
}

UnifiedSensor_t ds18b20Sensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
        lastMeasurement = currentMilliseconds;
        sensors.requestTemperatures();
        data.sensorType = S_TYPE_DS18B20;
        data.temperature = sensors.getTempCByIndex(0);
        return data;
    }
    data.sensorType = S_TYPE_INVALID;
    return data;
}