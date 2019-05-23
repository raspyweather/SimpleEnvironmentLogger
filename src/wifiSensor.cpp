#include "sensor.h"
#include <cstdint>
#include <wifiSensor.h>
#include <ESP8266WiFi.h>

UnifiedSensor_t wifiSensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    float rssi = WiFi.RSSI();
    if (!isnan(rssi))
    {
        data.sensorType = S_TYPE_WIFI;
        data.signalStrength = rssi;
    }
    else
    {
        Serial.println("Unable to read wifi rssi");
    }
    return data;
}
void wifiSensor::init()
{
    Serial.println(F("Wifi sensor enabled"));
}