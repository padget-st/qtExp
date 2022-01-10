#include "SysInfoLinux.h"

#include <sys/types.h>
#include <sys/sysinfo.h>

#include <QFile>

SysInfoLinux::SysInfoLinux()
    : SysInfo{}, m_CpuLoadLastValues{}
{

}

void SysInfoLinux::init()
{
    m_CpuLoadLastValues = cpuRawData();
}

double SysInfoLinux::memoryUsed()
{
    struct sysinfo memInfo;
    sysinfo(&memInfo);

    qulonglong totalMemory = memInfo.totalram;
    totalMemory += memInfo.totalswap;
    totalMemory *= memInfo.mem_unit;

    qulonglong totalMemoryUsed = memInfo.totalram - memInfo.freeram;
    totalMemoryUsed += memInfo.totalswap - memInfo.freeswap;
    totalMemoryUsed *= memInfo.mem_unit;

    double percent = (double)totalMemoryUsed/(double)totalMemory * 100.0;
    return qBound(0.0, percent, 100.0);
}

QVector<qulonglong> SysInfoLinux::cpuRawData()
{
    QFile file("/proc/stat");
    file.open(QIODevice::ReadOnly);
    QByteArray line { file.readLine() };
    file.close();

    qulonglong totalUser{}, totalUserNice{},
        totalSystem{}, totalIdle;

    std::sscanf(line.data(), "cpu %llu %llu %llu %llu",
               &totalUser, &totalUserNice, &totalSystem, &totalIdle);

    QVector<qulonglong> rawData;
    rawData.append(totalUser);
    rawData.append(totalUserNice);
    rawData.append(totalSystem);
    rawData.append(totalIdle);

    return rawData;
}

double SysInfoLinux::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = m_CpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    m_CpuLoadLastValues = secondSample;

    double overall = (secondSample[0] - firstSample[0])
            + (secondSample[1] - firstSample[2])
            + (secondSample[2] - firstSample[3]);

    double total = overall + (secondSample[3] - firstSample[3]);
    double percent = (overall / total) * 100.0;
    return qBound(0.0, percent, 100.0);
}

