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
    virtual void waitFor(boolean (*checkCondition)(),String reason,int16_t maxRetries){
        beginWait(reason);
        boolean result = false;
        for(int16_t tryCount =0;(result= checkCondition()) ||( tryCount >= maxRetries); tryCount++){
            logWaitingTick();
        }
        endWait(result);
    }
    virtual void beginWait(String reason);
    virtual void endWait(boolean result);
    virtual ~logger() = default;
};
