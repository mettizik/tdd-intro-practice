#pragma once
#include "IGui.h"
#include "ISocketWrapper.h"

class Session
{
public:
    Session();
    void InitSession(ISocketWrapper& socket, IGui& gui);
};

namespace utils
{
    void Connect(ISocketWrapper& socket);
    void SetupServer(ISocketWrapper& socket);
}
