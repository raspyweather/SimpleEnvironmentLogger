#pragma once
#include <cstdint>
#include "unifiedSensor.h"
class genericDisplay
{
private:
    /* data */
public:
    genericDisplay(/* args */) = default;
    virtual void init() = 0;
    virtual void processData(UnifiedSensor_t input) = 0;
    virtual ~genericDisplay() = default;
};
