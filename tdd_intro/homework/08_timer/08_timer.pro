include(../../gtest.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += NOMINMAX

HEADERS += \
    Timer.h \
    ITimer.h

SOURCES += \
    Timer.cpp \
    test.cpp
