include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    filemock.cpp

HEADERS += \
    ifile.h \
    filemock.h \
    stdafx.h
