
#include <Arduino.h>
const String sensorNames[] = {
    "Unknown Type",
    "DS18B20",
    "BMP280",
    "CCS811",
    "DHT22"};
typedef enum
{
    S_TYPE_UNKNOWN = 0,
    S_TYPE_DS18B20,
    S_TYPE_BMP280,
    S_TYPE_CCS811,
    S_TYPE_DHT22,
    S_TYPE_INVALID
} SensorType_t;

typedef struct
{
    SensorType_t sensorType = S_TYPE_UNKNOWN;
    float tvoc = NAN;
    float temperature = NAN;
    float humidity = NAN;
    float pressure = NAN;
} UnifiedSensor_t;
