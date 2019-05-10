#pragma once
#include <cstdint>
#include "unifiedSensor.h"
class sensor
{
private:
    /* data */
public:
    sensor(/* args */) = default;
    virtual void init() = 0;
    virtual UnifiedSensor_t measureData(uint32_t currentMilliseconds) = 0;
    virtual ~sensor() = default;
};
