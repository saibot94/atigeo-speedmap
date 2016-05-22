#ifndef LOGDEVICE_H
#define LOGDEVICE_H

#pragma once

/* CAF has its own logging */
#ifndef USE_CAF

#include "LogDeviceSeverity.h"
#include "LogWriter.h"
#include "CritSect.h"
#include <string>
#include <vector>

#define LOGDEVICE_VERSION               4   /* increase with every change to the structure */

#ifndef ushort
typedef unsigned short ushort;
#endif

/** \brief Log a debug message - is only enabled when you compile a debug binary */
#if (_MSC_VER > 1200) /* vc6 */
    #ifdef _DEBUG
        #define LOG_DEBUG(text, ...) CLogDevice::get()->log(CLogDeviceSeverity::Debug,  __LINE__, __FILE__, text , __VA_ARGS__)
    #else
        #define LOG_DEBUG(text, ...)
    #endif

    /** \brief The Info Macro just display the given text without adding anything*/
    #define LOG_INFO(text, ...)     CLogDevice::get()->log(CLogDeviceSeverity::Info,  __LINE__, __FILE__, text , __VA_ARGS__)
    /** \brief The Error Macro adds source code file and line to the message */
    #define LOG_ERROR(text, ...)    CLogDevice::get()->log(CLogDeviceSeverity::Error,  __LINE__, __FILE__, text , __VA_ARGS__)
    /** \brief The Warning Macro adds source code file and line to the message */
    #define LOG_WARNING(text, ...)  CLogDevice::get()->log(CLogDeviceSeverity::Warning,  __LINE__, __FILE__, text , __VA_ARGS__)
    /** \brief Log a fatal error */
    #define LOG_FATAL(text, ...)    CLogDevice::get()->log(CLogDeviceSeverity::Fatal,  __LINE__, __FILE__, text , __VA_ARGS__)
#endif

/** \brief LogDevice is a singleton which can write messages to different sinks

\author Ralph Grewe
\version 1.0
\date 20081104

\par Description
The LogDevice privedes a simple mechanismus for writing log messages to different devices. It is
a singleton which makes it easily accessible from anywhere in the code. The output can be written to
one or more LogWriters.

\par Usage
You can use one of the log() methods to log an entry:
\code LogDevice::get()->log(IComAdaptor::Debug, "DataRecorderTask build %s %s", __DATE__, __TIME__);

Or you can use one of the LOG_INFO, LOG_ERROR, LOG_WARNING macros which automatically set the severity and
may display additional information:
\code LOG_ERROR("IDoAction error: %s", text.c_str());
Logs the printf()-style format string given to LOG_ERROR prefixed by source code file name and line
*/
class CLogDevice
{
public:
    static ushort GetVersion() { return LOGDEVICE_VERSION;};

    /** \brief Get a pointer to the LogDevice
    \par
    As necessary for a singleton, this method delivers you a pointer to the log device
    */
    static CLogDevice* get();

    /** \brief Log an std::string entry*/
    bool log(const std::string& message, CLogDeviceSeverity::Severity severity = CLogDeviceSeverity::Info);

    /** \brief log an printf() format string*/
    bool log( CLogDeviceSeverity::Severity severity, const char* format, ...);

    bool log( CLogDeviceSeverity::Severity severity, const unsigned long lineNo, const char *fileName, const char* format, ...);

    /** \brief Add a log writer */
    bool addLogWriter( CLogWriter* logWriter);

    /** \brief Remove a log writer */
    bool removeLogWriter( CLogWriter* logWriter);

    /** \brief get pointer to logwrite with special name */
    CLogWriter* getLogWriter( const char *name);

    static bool RedirectOutput(CLogDevice *pDevice, ushort version); /* redirekts output to pDevice, the own device is not used anymore (for synchronizing dlls), pDevice = 0 switches of redirecting */

    bool SetLogLevel(unsigned int logLevel); /* set level and all higher levels, act as global filter, each logWriter as in addition to this its own => saves resources if using this */

private:
    static CLogDevice   sSelf;              /** \brief The one and only LogDevice that exists, until somebody sets another...*/
    static CLogDevice  *mpDevice;           /** \brief Pointer to the one and only LogDevice that exists*/
    CCritSect           mWritersCritSect;   /** \brief We need a mutex to lock some operations*/

    typedef std::vector<CLogWriter*> TLogWriterArray;
    TLogWriterArray     mWriters;
    unsigned int        mLogLevelsEnabled;


    /** \brief Constructor is private to control creation of objects*/
    CLogDevice(void);
    /** \brief The destructor is private, too */
    #if (_MSC_VER <= 1200)
        public:
    #endif
    ~CLogDevice(void);

    /** \par Description
    This is a private method which formats the current system time into a human readable form and appends
    it to the given string
    */
    static int appendSystemTime(char* buffer);

    /** \brief Write LogLine's to the LogWriters*/
    void writeLog(const char* text, CLogDeviceSeverity::Severity severity, const char *fileName, const unsigned long lineNo);
};

/* the following defines the macros so they work in VisualC6, vc6 does not know macros with variable parameter lists */
#if (_MSC_VER <= 1200) /* vc6 */
    #include "stdarg.h"
    inline bool LOG_DEBUG(const char *formatStr,...)
    {
        char str[1024]; va_list argptr; va_start(argptr,formatStr);
        _vsnprintf(str, sizeof(str), formatStr, argptr); str[sizeof(str)-1] = 0;
        return CLogDevice::get()->log(CLogDeviceSeverity::Debug, 0,0, "%s", str);
    };
    inline bool LOG_INFO(const char *formatStr,...)
    {
        char str[1024]; va_list argptr; va_start(argptr,formatStr);
        _vsnprintf(str, sizeof(str), formatStr, argptr); str[sizeof(str)-1] = 0;
        return CLogDevice::get()->log(CLogDeviceSeverity::Info, 0,0, "%s", str);
    };
    inline bool LOG_WARNING(const char *formatStr,...)
    {
        char str[1024]; va_list argptr; va_start(argptr,formatStr);
        _vsnprintf(str, sizeof(str), formatStr, argptr); str[sizeof(str)-1] = 0;
        return CLogDevice::get()->log(CLogDeviceSeverity::Warning, 0,0, "%s", str); /* __LINE__ seems not to work with inline... */
    };
    inline bool LOG_ERROR(const char *formatStr,...)
    {
        char str[1024]; va_list argptr; va_start(argptr,formatStr);
        _vsnprintf(str, sizeof(str), formatStr, argptr); str[sizeof(str)-1] = 0;
        return CLogDevice::get()->log(CLogDeviceSeverity::Error, 0,0, "%s", str);
    };
    inline bool LOG_FATAL(const char *formatStr,...)
    {
        char str[1024]; va_list argptr; va_start(argptr,formatStr);
        _vsnprintf(str, sizeof(str), formatStr, argptr); str[sizeof(str)-1] = 0;
        return CLogDevice::get()->log(CLogDeviceSeverity::Fatal, 0,0, "%s", str);
    };
#endif

/* ********** CAF has it's own logging *********************************** */
#else

    #include <caf/caf.h>
    #include "LogDeviceSeverity.h"

    #define LOG_INFO(text, ...)     CAF::Log( CAF::INFO,    "algoutils", text, __VA_ARGS__)
    #define LOG_ERROR(text, ...)    CAF::Log( CAF::ERR,     "algoutils", text, __VA_ARGS__)
    #define LOG_WARNING(text, ...)  CAF::Log( CAF::WARNING, "algoutils", text, __VA_ARGS__)
    #define LOG_FATAL(text, ...)    CAF::Log( CAF::FATAL,   "algoutils", text, __VA_ARGS__)
    #ifdef _DEBUG
        #define LOG_DEBUG(text, ...) CAF::Log( CAF::DEBUG,  "algoutils", text, __VA_ARGS__)
    #else
        #define LOG_DEBUG(text, ...)
    #endif

#endif

#endif // LOGDEVICE_H
