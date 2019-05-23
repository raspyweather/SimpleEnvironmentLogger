#include "ccs811Sensor.h"

UnifiedSensor_t ccs811Sensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    ccs.readData();
    data.sensorType = S_TYPE_CCS811;

    data.temperature = ccs.calculateTemperature();
    data.tvoc = ccs.getTVOC();
    return data;
}
void ccs811Sensor::init()
{
    Serial.print(F("Connecting to CCS811"));
    while (!ccs.begin())
    {
        Serial.print(F("."));
        delay(500);
    }
    //ccs.setDriveMode(CCS811_DRIVE_MODE_250MS);
    Serial.println(F("[OK]"));
}
void ccs811Sensor::calibrate()
{
    Serial.println(F("Calibrating CCS811"));
    while (!ccs.available())
    {
        Serial.print(F("."));
        delay(500);
    }
    Serial.println(F("[OK]"));
    float temp = getTemp();
    float humidity = getHumidity();
    ccs.setEnvironmentalData(humidity, temp);

    float ccsTemp = ccs.calculateTemperature();
    Serial.print(F("CCS811 calibration Temperature: "));
    Serial.println(ccsTemp);
    ccs.setTempOffset(ccsTemp - 25);
}