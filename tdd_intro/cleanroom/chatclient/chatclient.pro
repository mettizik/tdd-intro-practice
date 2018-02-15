include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    socketwrapper.cpp \
    Session.cpp \
    ChatUtils.cpp

HEADERS += \
    socketwrapper.h \
    ISocketWrapper.h \
    IGui.h \
    Session.h \
    ChatUtils.h

LIBS += \
    Ws2_32.lib \
    Mswsock.lib \
    AdvApi32.lib
