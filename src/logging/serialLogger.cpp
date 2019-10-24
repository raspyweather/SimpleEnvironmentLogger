#include "serialLogger.h"
#define Baudrate 57600

void serialLogger::init(){
    serialPort.begin(Baudrate);
}
void serialLogger::logError(String message){
    serialPort.println("!!!"+message);
}
void serialLogger::logData(uint32_t currentMilliseconds, UnifiedSensor_t sensorData){

  if (sensorData.sensorType == S_TYPE_INVALID)
  {
    return;
  }
  serialPort.print(sensorNames[sensorData.sensorType]);
  serialPort.print(F(" "));
  if (!isnan(sensorData.humidity))
  {
    serialPort.print(sensorData.humidity);
    serialPort.print(F("%,"));
  }
  if (!isnan(sensorData.temperature))
  {
    serialPort.print(sensorData.temperature);
    serialPort.print(F("°C,"));
  }
  if (!isnan(sensorData.pressure))
  {
    serialPort.print(sensorData.pressure);
    serialPort.print(F("hPa,"));
  }
  if (!isnan(sensorData.tvoc))
  {
    serialPort.print(sensorData.tvoc);
    serialPort.print(F(""));
  }
  if (!isnan(sensorData.signalStrength))
  {
    serialPort.print(sensorData.signalStrength);
    serialPort.print(F(""));
  }
  if (!isnan(sensorData.PM10))
  {
    serialPort.print(sensorData.PM10);
    serialPort.print(F(" PM10 "));
  }
  if (!isnan(sensorData.PM2_5))
  {
    serialPort.print(sensorData.PM2_5);
    serialPort.print(F(" PM2.5 "));
  }
  serialPort.println();

}
void serialLogger::logWaitingTick(){
    serialPort.print(".");
}
void serialLogger:: waitFor(boolean (*checkCondition)(),String description,int16_t maxTries){
    serialPort.print(description);
    int16_t ctr=0;
    for(;checkCondition()|| maxTries >=ctr || ctr==-1 ;ctr++){
        logWaitingTick();
    }
    if(ctr>=maxTries){
        serialPort.print("[Failed]");
    }
    else{
        serialPort.print("[Ok]");
    }
}