#include "windDirectionSensor.h"

void windDirectionSensor::init()
{
    Serial.println("Connecting to windDirectionSensor");
    pinMode(A0, INPUT_PULLDOWN_16);
    Serial.println(F("[OK]"));
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

UnifiedSensor_t windDirectionSensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
        lastMeasurement = currentMilliseconds;
        data.sensorType = S_TYPE_WINDDIRERCTIONSENSOR;
        data.windDirection = (int)((int)(mapfloat(analogRead(A0) % 725, 0, 725, 360, 0) + 182)) % 360;
        return data;
    }
    data.sensorType = S_TYPE_INVALID;
    return data;
}
