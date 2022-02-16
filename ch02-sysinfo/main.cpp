#include "mainwindow.h"

#include <QApplication>
#include "Sysinfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SysInfo::instance().init();
    MainWindow w;
    w.show();
    return a.exec();
}
