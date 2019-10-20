#include "ledLogger.h"

void ledLogger::init(){
    pinMode(pinAddress, OUTPUT);
}
void ledLogger::logData(uint32_t currentMilliseconds, UnifiedSensor_t data){
    auto previous = digitalRead(pinAddress);
    if(previous==HIGH){
        digitalWrite(pinAddress,LOW);
    }
    else{
       digitalWrite(pinAddress,HIGH);
    }
}

void ledLogger::logError(String message){
    for(uint8_t i=0;i<5;i++)
    {
        digitalWrite(pinAddress,HIGH);
        delay(100);
        digitalWrite(pinAddress,LOW);
        delay(100);
    }
}
void ledLogger::logWaitingTick(){
    digitalWrite(pinAddress,LOW);
    delay(200);
    digitalWrite(pinAddress,HIGH);
    delay(200);
    digitalWrite(pinAddress,LOW);

}