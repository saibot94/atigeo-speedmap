#ifndef LOGDEVICESEVERITY_H_
#define LOGDEVICESEVERITY_H_

class CLogDeviceSeverity
{
public: 
    enum Severity 
    {
        Debug   = 0x01,
        Info    = 0x02,
        Warning = 0x04,
        Error   = 0x08,
        Fatal   = 0x10,
        All     = 0x1F
    };
};

#endif // LOGDEVICESEVERITY_H_
