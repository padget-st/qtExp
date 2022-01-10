#include "Sysinfo.h"
#include <QtGlobal>

#ifdef Q_OS_WIN
    #include "SysInfoWindows.h"
#elif defined(Q_OS_LINUX)
    #include "SysInfoLinux.h"
#endif

SysInfo& SysInfo::instance()
{
    #ifdef Q_OS_WIN
        static SysInfoWindows singleton;
    #elif defined(Q_OS_LINUX)
        static SysInfoLinux singleton;
    #endif

    return singleton;
}

SysInfo::SysInfo()
{

}

SysInfo::~SysInfo()
{

}
