#pragma once
#include "ISocketWrapper.h"

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
    bool HandShake(ISocketWrapper::SockPtr socketConnection, const std::string& nickName);
}
