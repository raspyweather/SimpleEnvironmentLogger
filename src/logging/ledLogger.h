#pragma once
#include <cstdint>
#include "logger.h"
#include "../sensor.h"
#include "../unifiedSensor.h"

class ledLogger: public logger
{
private:
    /* data */
    uint8_t pinAddress;
public:
    ledLogger(/* args */) = default;
    void init();
    void logError(String message);
    void logWaitingTick();
    void logData(uint32_t currentMilliseconds, UnifiedSensor_t data);
    ~ledLogger() = default;
};
