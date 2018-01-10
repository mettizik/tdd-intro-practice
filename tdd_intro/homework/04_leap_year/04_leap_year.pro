TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += conan_basic_setup
include(../../conanbuildinfo.pri)

SOURCES += \
    04_leap_year.cpp
