#include "SysInfoWindows.h"
#include <windows.h>

SysInfoWindows::SysInfoWindows()
    : SysInfo{}, m_cpuLoadLastValues{}
{}

double SysInfoWindows::memoryUsed()
{
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx( &memStatus );
    unsigned long long memPhysUsed{ memStatus.ullTotalPhys - memStatus.ullAvailPhys };

    return static_cast<double>(memPhysUsed)/memStatus.ullTotalPhys * 100.0;
}

void SysInfoWindows::init()
{
    m_cpuLoadLastValues = cpuRawData();
}

QVector<quint64> SysInfoWindows::cpuRawData()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    QVector<quint64> rawData{};

    rawData.append(convertFileTime(idleTime));
    rawData.append(convertFileTime(kernelTime));
    rawData.append(convertFileTime(userTime));

    return rawData;
}

quint64 SysInfoWindows::convertFileTime(const FILETIME& filetime) const
{
    ULARGE_INTEGER largeInt{};
    largeInt.LowPart = filetime.dwLowDateTime;
    largeInt.HighPart = filetime.dwHighDateTime;
    return largeInt.QuadPart;
}

double SysInfoWindows::cpuLoadAverage()
{
    auto firstSample  { m_cpuLoadLastValues };
    auto secondSample { cpuRawData() };
    m_cpuLoadLastValues = secondSample;

    quint64 currIdle    { secondSample[0] - firstSample[0] };
    quint64 currKernel  { secondSample[1] - firstSample[1] };
    quint64 currUser    { secondSample[2] - firstSample[2] };
    quint64 currSystem  { currKernel + currUser };

    double percent{ (currSystem - currIdle) * 100.0 / currSystem };
    return qBound(0.0, percent, 100.0);
}

