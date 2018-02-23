#pragma once
#include "ISocketWrapper.h"
#include "IChatSession.h"
#include "IGui.h"

#include <string>
#include <memory>

namespace sessionUtils
{
    const std::string GetHost();
    const int16_t GetPort();
    const std::string GetListenMessage();
    const std::string GetHelloMessage();

    ISocketWrapper::SockPtr Connect(ISocketWrapper& socket);
    ISocketWrapper::SockPtr SetupServer(ISocketWrapper& socket);
    std::string ReadHandShake(ISocketWrapper& socket);
    void SendHandShake(ISocketWrapper& socket, const std::string& nickname);

    IChatSession_ptr CreateNewSession(ISocketWrapper& socket, IGui& gui);
    IChatSession_ptr StartSession(ISocketWrapper& socket, IGui& gui, const std::string& nickname);
}
