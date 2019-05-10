#pragma once
#define DS18PIN D6
#include <Arduino.h>
#include "sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>
class ds18b20Sensor : public sensor
{
private:
    OneWire oneWire{DS18PIN};
    DallasTemperature sensors{&oneWire};
    uint32_t lastMeasurement = 0;
    uint32_t minMeasureDelay = 750;
public:
    ds18b20Sensor() = default;
    ~ds18b20Sensor() = default;
    UnifiedSensor_t measureData(uint32_t currentMilliseconds);
    void init();
};