#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include "SysInfoWidget.h"
#include <QtCharts/QPieSeries>

class CpuWidget : public SysInfoWidget
{
public:
    Q_OBJECT
public:
    explicit CpuWidget(QWidget* parent = nullptr);

protected slots:
    void updateSeries() override;

private:
    QtCharts::QPieSeries* mSeries;
};

#endif // CPUWIDGET_H
