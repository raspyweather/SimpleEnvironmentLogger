#pragma once
#include <cstdint>
#include "logger.h"
#include "../sensor.h"
#include "../unifiedSensor.h"

class multiLogger: public logger
{
private:
    /* data */
    logger**loggers;
public:
    multiLogger(logger* loggers[]);
    void init();
    void logError(String message);
    void logWaitingTick();
    void logData(uint32_t currentMilliseconds, UnifiedSensor_t sensor);
    void beginWait(String waitingReason);
    void endWait(boolean result);
    void waitFor(boolean (*checkCondition)(),String reason,int16_t maxRetries);
    ~multiLogger() = default;
};