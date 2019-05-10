#pragma once
#include "sensor.h"
#include <cstdint>
#include <Adafruit_BMP280.h>
class bmp280Sensor : public sensor
{
private:
    Adafruit_BMP280 bmp;

public:
    bmp280Sensor() = default;
    ~bmp280Sensor() = default;
    void init();
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
    float getTemp();
};
