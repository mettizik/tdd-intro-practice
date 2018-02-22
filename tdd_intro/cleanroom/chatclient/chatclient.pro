include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    socketwrapper.cpp \
    sessionutils.cpp \
    clientsession.cpp \
    serversession.cpp

HEADERS += \
    socketwrapper.h \
    ISocketWrapper.h \
    IGui.h \
    sessionutils.h \
    clientsession.h \
    serversession.h \
    IChatSession.h

LIBS += \
    Ws2_32.lib \
    Mswsock.lib \
    AdvApi32.lib
