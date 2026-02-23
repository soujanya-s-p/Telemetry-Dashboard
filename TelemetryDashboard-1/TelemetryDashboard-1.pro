QT += core gui widgets network charts

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    telemetryserver.cpp \
    dataparser.cpp

HEADERS += \
    mainwindow.h \
    telemetryserver.h \
    dataparser.h

FORMS += \
    mainwindow.ui
