#pragma once
#include <cstdint>
#include "logger.h"
#include "../sensor.h"
#include "../unifiedSensor.h"
#define SerialType HardwareSerial

class serialLogger: public logger
{
private:
    SerialType serialPort = Serial;
    /* data */
public:
    serialLogger(/* args */) = default;
    void init();
    void logError(String message);
    void logWaitingTick();
    void logData(uint32_t currentMilliseconds, UnifiedSensor_t data);
    ~serialLogger() = default;
};
