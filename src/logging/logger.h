#pragma once
#include <cstdint>
#include "../unifiedSensor.h"

class logger
{
private:
    /* data */
public:
    logger(/* args */) = default;
    virtual void init();
    virtual void logError(String message);
    virtual void logWaitingTick();
    virtual void logData(uint32_t currentMilliseconds, UnifiedSensor_t sensor);
    virtual ~logger() = default;
};
