include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    socketwrapper.cpp \
    ServerSession.cpp \
    ClientSession.cpp \
    sessionutils.cpp

HEADERS += \
    socketwrapper.h \
    ISocketWrapper.h \
    IGui.h \
    ServerSession.h \
    ClientSession.h \
    sessionutils.h

LIBS += \
    Ws2_32.lib \
    Mswsock.lib \
    AdvApi32.lib
