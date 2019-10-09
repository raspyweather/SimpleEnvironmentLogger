#include "bme280Sensor.h"
#include "sensor.h"
#include "unifiedSensor.h"

void bme280Sensor::init()
{
    Serial.print(F("Connecting to BME280"));
    while (!bme.begin())
    {
        Serial.print(F("."));
        delay(500);
    }
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
        Adafruit_BME280::SAMPLING_X1,
        Adafruit_BME280::SAMPLING_X1,
        Adafruit_BME280::SAMPLING_X1,
        Adafruit_BME280::FILTER_X2,
        Adafruit_BME280::STANDBY_MS_1000);
    minMeasureDelay = 300;
    Serial.println(F("[OK]"));
    
}

UnifiedSensor_t bme280Sensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    data.sensorType = S_TYPE_INVALID;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
            bme.takeForcedMeasurement();
            data.sensorType = S_TYPE_BME280;
           lastTemp =  data.temperature = bme.readTemperature();
            data.pressure = bme.readPressure() / 100.0;
           lastHumidity =  data.humidity = bme.readHumidity();
        return data;
    }
    return data;
}

float bme280Sensor::getTemp(){
    return lastTemp;
}
float bme280Sensor::getHumidity(){
    return lastHumidity;
}