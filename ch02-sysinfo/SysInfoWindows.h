#ifndef SYSINFOWINDOWS_H
#define SYSINFOWINDOWS_H

#include <QtGlobal>
#include <QVector>
#include "Sysinfo.h"

typedef struct _FILETIME FILETIME;

class SysInfoWindows : public SysInfo
{
public:
    SysInfoWindows();

    void    init() override;
    double  cpuLoadAverage() override;
    double  memoryUsed() override;

private:
    QVector<quint64> cpuRawData();
    quint64 convertFileTime(const FILETIME& filetime) const;
private:
    QVector<quint64> m_cpuLoadLastValues;
};

#endif // SYSINFOWINDOWS_H
