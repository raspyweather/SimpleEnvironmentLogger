#include "multiLogger.h"

multiLogger::multiLogger(logger *_loggers[]){
    loggers = _loggers;
}
void multiLogger::init(){
    int16_t loggerCount = sizeof(loggers)/sizeof(*loggers);
    for(int16_t i = 0;i<loggerCount;i++)
    {
        loggers[i]->init();
    }    
}
void multiLogger::beginWait(String reason){
    int16_t loggerCount = sizeof(loggers)/sizeof(*loggers);
    for(int16_t i = 0;i<loggerCount;i++)
    {
        loggers[i]->beginWait(reason);
    }
}
void multiLogger::endWait(boolean result){
    int16_t loggerCount = sizeof(loggers)/sizeof(*loggers);
    for(int16_t i = 0;i<loggerCount;i++)
    {
        loggers[i]->endWait(result);
    }
}