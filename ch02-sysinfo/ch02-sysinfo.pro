QT       += core gui charts
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = ch02-sysinfo
TEMPLATE = app

SOURCES += \
    CpuWidget.cpp \
    SysInfoWidget.cpp \
    Sysinfo.cpp \
    main.cpp \
    mainwindow.cpp \
   # CpuWidget.cpp \
   # MemoryWidget.cpp \
   # SysInfoWidget.cpp

HEADERS += \
    CpuWidget.h \
    SysInfoWidget.h \
    Sysinfo.h \
    mainwindow.h \
   # CpuWidget.h \
   # MemoryWidget.cpp \
   # SysInfoWidget.cpp

windows {
    SOURCES += SysInfoWindows.cpp
    HEADERS += SysInfoWindows.h
}

linux {
    SOURCES += SysInfoLinux.cpp
    HEADERS += SysInfoLinux.h
}

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
