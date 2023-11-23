QT += core gui charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chart.cpp \
    ImpactDetail.cpp \
    ImpactType.cpp \
    Impacts.cpp \
    ServerImpactFactory.cpp \
    SystemInfo.cpp \
    component.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Chart.h \
    ImpactDetail.h \
    ImpactType.h \
    Impacts.h \
    ServerImpact.h \
    ServerImpactFactory.h \
    SystemInfo.h \
    component.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
