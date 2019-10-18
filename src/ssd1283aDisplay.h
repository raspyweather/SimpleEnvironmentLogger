#pragma once
#include <cstdint>
#include "unifiedSensor.h"
#include "genericDisplay.h"

class ssd1283aDisplay : public genericDisplay
{
private:
    /* data */
public:
    ssd1283aDisplay(/* args */) = default;
     void init() ;
     void processData(UnifiedSensor_t input) ;
     ~ssd1283aDisplay() = default;
};
