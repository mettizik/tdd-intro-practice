#pragma once
#include "ISocketWrapper.h"

#include <string>
#include <memory>

namespace sessionUtils
{
    const std::string GetHost();
    const int16_t GetPort();
    const std::string GetListenMessage();
    const std::string GetHandshareErrorMessage();
    const std::string GetFullName(const std::string& userName);

    ISocketWrapper::SockPtr Connect(ISocketWrapper& socket);
    ISocketWrapper::SockPtr SetupServer(ISocketWrapper& socket);
}
