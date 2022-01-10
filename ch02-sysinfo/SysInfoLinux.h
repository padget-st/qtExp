#ifndef SYSINFOLINUX_H
#define SYSINFOLINUX_H

#include <QtGlobal>
#include <QVector>
#include "Sysinfo.h"

class SysInfoLinux : public SysInfo
{
public:
    SysInfoLinux();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<qulonglong> cpuRawData();
    QVector<qulonglong> m_CpuLoadLastValues;
};

#endif // SYSINFOLINUX_H
