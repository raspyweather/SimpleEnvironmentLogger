#include "windSpeedSensor.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
const int rs485RX = D6; // Recieve pin for software serial (Rx on RS485 adapter)
const int rs485Tx = D7; // Send pin for software serial (Tx on RS485 adapter)
SoftwareSerial RS485Serial(rs485RX, rs485Tx);

void windSpeedSensor::init()
{
    Serial.println("Connecting to WindSpeedSensor");
    RS485Serial.begin(9600);
    Serial.println(F("[OK]"));
}

UnifiedSensor_t windSpeedSensor::measureData(uint32_t currentMilliseconds)
{
    UnifiedSensor_t data;
    if (currentMilliseconds - lastMeasurement > minMeasureDelay)
    {
        lastMeasurement = currentMilliseconds;
        data.sensorType = S_TYPE_WINDSPEEDSENSOR;
        const byte Anemometer_request[] = {0x01, 0x03, 0x00, 0x16, 0x00, 0x01, 0x65, 0xCE}; // inquiry frame
        RS485Serial.write(Anemometer_request, sizeof(Anemometer_request));
        RS485Serial.flush();
        byte Anemometer_buf[8];
        RS485Serial.readBytes(Anemometer_buf, 8);
        data.windSpeed = Anemometer_buf[4] * 0.1;
        return data;
    }
    data.sensorType = S_TYPE_INVALID;
    return data;
}
