include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    socketwrapper.cpp \
    ChatSession.cpp \
    ChatSessionUtils.cpp

HEADERS += \
    socketwrapper.h \
    ISocketWrapper.h \
    IGui.h \
    ChatSession.h \
    ChatSessionUtils.h

LIBS += \
    Ws2_32.lib \
    Mswsock.lib \
    AdvApi32.lib
