TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    01_bob.cpp

CONFIG += conan_basic_setup
include(../../conanbuildinfo.pri)
