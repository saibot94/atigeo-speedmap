#ifndef LOGWRITER_H_
#define LOGWRITER_H_

#include "LogDeviceSeverity.h"

class CLogWriter 
{
public:
    CLogWriter();
    virtual ~CLogWriter();
    virtual void logMessage(CLogDeviceSeverity::Severity severity, const char* message, const char *fileName, const unsigned long lineNo);
    virtual const char *GetName() = 0; 
    
    virtual bool SetLogLevel(unsigned int logLevel); /* set level and all higher levels */
    virtual bool LogLevelEnable(unsigned int);
    virtual bool LogLevelDisable(unsigned int);
    
    static const char *GetSevStr(CLogDeviceSeverity::Severity severity);

protected:
    virtual void log(CLogDeviceSeverity::Severity severity, const char* message, const char *fileName, const unsigned long lineNo) = 0;
    CLogWriter(const CLogWriter& ) {}
    
    unsigned int mLogLevelsEnabled;
};

#endif // LOGWRITER_H_
