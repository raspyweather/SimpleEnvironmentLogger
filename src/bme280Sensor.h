#pragma once
#include "sensor.h"
#include <cstdint>
#include <Adafruit_BME280.h>
class bme280Sensor : public sensor
{
private:
    Adafruit_BME280 bme;

public:
    bme280Sensor() = default;
    ~bme280Sensor() = default;
    void init();
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
    float getTemp();
    float getHumidity();
};
