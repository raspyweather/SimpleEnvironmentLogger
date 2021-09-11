#include "waterCounterSensor.h"

void waterCounterSensor::init()
{
    pinMode(WATERCOUNTERSENSORPIN, INPUT_PULLUP);
}

void waterCounterSensor::resetCount()
{
    count = 0;
}

UnifiedSensor_t waterCounterSensor::measureData(uint32_t currentMilliseconds)
{
    if (currentMilliseconds - lastImpulse > minDelay)
    {
        bool currentState = digitalRead(WATERCOUNTERSENSORPIN) == HIGH;
        if (previousState && !currentState)
        {
            count++;
        }

        previousState = currentState;
        lastImpulse = currentMilliseconds;
    }

    UnifiedSensor_t data;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
        lastMeasurement = currentMilliseconds;
        data.sensorType = S_TYPE_WATERCOUNTER;
        data.waterCount = count;
        return data;
    }
    data.sensorType = S_TYPE_INVALID;
    return data;
}
