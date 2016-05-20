#ifndef LOGWRITERMODPLUGIN_H_
#define LOGWRITERMODPLUGIN_H_

#include "LogDevice.h"

class LogWriterModPlugin : public CLogWriter
{
public:
  LogWriterModPlugin(CEvtPlugIn *plugin) : mPlugin(plugin)
  {
  }

  ~LogWriterModPlugin(void)
  {
  }

  const char *GetName() {return "LogWriterModPlugin";};

private:
    virtual void log(CLogDeviceSeverity::Severity severity, const char* message, const char *fileName, const unsigned long lineNo)
    {
    SYSTEMTIME time; lineNo; fileName;
    
    GetLocalTime(&time);
    
    _snprintf_s(mBuffer, mBufferSize, _TRUNCATE, "%02d:%02d:%02d.%03d: %s: %s", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, GetSevStr( severity), message);
    mPlugin->TextPrint2Con(mBuffer);
    }

  CEvtPlugIn               *mPlugin;
  const static unsigned int mBufferSize = 512;
  char                      mBuffer[mBufferSize];
};

#endif // LOGWRITERMODPLUGIN_H_