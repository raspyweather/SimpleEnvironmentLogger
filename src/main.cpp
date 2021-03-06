#include <Wire.h>
#include "FS.h"
#include "InfluxDb.h"

#include "bme680Sensor.h"
#include "bmp280Sensor.h"
#include "ccs811Sensor.h"
#include "ds18b20Sensor.h"
#include "dht22Sensor.h"
#include "wifiSensor.h"
#include "sds011Sensor.h"
#include <ESP8266WiFi.h>

#define INFLUXDB_HOST "influxHost"
#define INFLUXDB_PORT 8086
#define INFLUXDB_DATABASE "influxDbName"
#define INFLUXDB_USER "influxUser"
#define INFLUXDB_PASS "influxPass"
#define INFLUX_MEASUREMENT "influxMeasurement"
#define WLAN_SSID "your ssid here"
#define WLAN_PASS "your pass here"
void connectToInflux();
void initWifi();

Influxdb influx(INFLUXDB_HOST, INFLUXDB_PORT);

bmp280Sensor *tempSensor;
dht22Sensor *humiditySensor;
sensor *sensors[7];

uint32_t lastMeasurement = 0;
uint32_t minMeasureDelay = 1000;
bool blinkState = false;

int sensorsLength = sizeof(sensors) / sizeof(sensors[0]);

float getTemp()
{
  return tempSensor->getTemp();
}
float getHumidity()
{
  return (humiditySensor->measureData(millis())).humidity;
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Waiting for you to listem");
  digitalWrite(LED_BUILTIN, HIGH);
  for (int i = 0; i < 10 * 10; i++)
  {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, (blinkState = !blinkState) ? LOW : HIGH);
    delay(100);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Connecting to Wifi");
  initWifi();
  connectToInflux();
  tempSensor = new bmp280Sensor();
  humiditySensor = new dht22Sensor();
  auto ccs = (new ccs811Sensor(&getTemp, &getHumidity));
  sensors[0] = tempSensor;
  sensors[1] = ccs;
  sensors[2] = humiditySensor;
  sensors[3] = (new ds18b20Sensor());
  sensors[4] = (new wifiSensor());
  sensors[5] = (new bme680Sensor());
  sensors[6] = (new sds011Sensor());

  Serial.println(F("Initialization started"));
  for (int i = 0; i < sensorsLength; i++)
  {
    sensors[i]->init();
  }

  ccs->calibrate();
  digitalWrite(LED_BUILTIN, LOW);
}
void initWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  Serial.print(F("Connecting to "));
  Serial.print(WLAN_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(F("[OK]"));
  Serial.print(F("IP:"));
  Serial.print(WiFi.localIP());
  WiFi.setAutoReconnect(true);
}
void connectToInflux()
{
  influx.setDbAuth(INFLUXDB_DATABASE, INFLUXDB_USER, INFLUXDB_PASS);
}

void PrepareForInflux(UnifiedSensor_t sensorData)
{
  if (sensorData.sensorType == S_TYPE_INVALID)
  {
    return;
  }
  InfluxData measurement(INFLUX_MEASUREMENT);
  measurement.addTag("sensor", sensorNames[sensorData.sensorType]);
  int ctr = 0;
  if (!isnan(sensorData.humidity))
  {
    measurement.addValue(F("humidity"), sensorData.humidity);
    ctr++;
  }
  if (!isnan(sensorData.temperature))
  {
    measurement.addValue(F("temperature"), sensorData.temperature);
    ctr++;
  }
  if (!isnan(sensorData.tvoc))
  {
    measurement.addValue(F("tvoc"), sensorData.tvoc);
    ctr++;
  }
  if (!isnan(sensorData.pressure))
  {
    measurement.addValue(F("pressure"), sensorData.pressure);
    ctr++;
  }
  if (!isnan(sensorData.signalStrength))
  {
    measurement.addValue(F("signalstrength"), sensorData.signalStrength);
    ctr++;
  }
  if (!isnan(sensorData.PM2_5))
  {
    measurement.addValue(F("PM2_5"), sensorData.PM2_5);
    ctr++;
  }
  if (!isnan(sensorData.PM10))
  {
    measurement.addValue(F("PM10"), sensorData.PM10);
    ctr++;
  }
  if (ctr == 0)
  {
    return;
  }
  influx.prepare(measurement);
}

void loop()
{
  uint32_t milliseconds = millis();
  if (milliseconds - lastMeasurement > minMeasureDelay)
  {
    lastMeasurement = milliseconds;
    for (int i = 0; i < sensorsLength; i++)
    {
      auto data = sensors[i]->measureData(millis());
      PrepareForInflux(data);
    }
    digitalWrite(LED_BUILTIN, (blinkState = !blinkState) ? LOW : HIGH);
    if (influx.write())
    {
      Serial.println("written to influx");
    }
    else
    {
      Serial.println("could not write to influx");
    }
  }
}