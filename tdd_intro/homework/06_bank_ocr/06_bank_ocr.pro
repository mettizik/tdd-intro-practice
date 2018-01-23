include(../../gtest.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    BankOcr.cpp \
    RecognizeDigitTests.cpp \
    RecognizeNumberTests.cpp \
    CheckNumberTests.cpp

HEADERS += \
    BankOcr.h
