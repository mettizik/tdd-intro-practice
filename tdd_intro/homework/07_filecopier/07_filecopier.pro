include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    FileCopier.cpp

HEADERS += \
    IFileSystem.h \
    FileCopier.h
