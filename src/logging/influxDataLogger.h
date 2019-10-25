#pragma once
//#include <cstdint>
#include "logger.h"
#include "../sensor.h"
#include "../unifiedSensor.h"
#ifdef ESP8266
#include "InfluxDb.h"

class influxDataLogger: public logger
{
private:
    /* data */
    influxConfig configuration;
    Influxdb influx;
public:
    influxDataLogger(influxConfig config)
    {
        configuration = config;
        influx = new Influxdb(configuration.host,configuration.port);
    }
    void init();
    void logData(uint32_t currentMilliseconds, UnifiedSensor_t sensor);
    ~influxDataLogger() = default;
};

class influxConfig
{
 public:
    String host ="influxHost";
    int16_t port =8086;
    String database ="influxDbName";
    String username ="influxUser";
    String password ="influxPass";
    String measurement ="influxMeasurement";
};
#endif