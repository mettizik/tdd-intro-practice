#pragma once
#include <string>
#include <memory>

class ISocketWrapper;

namespace sessionUtils
{
    const std::string GetHost();
    const int16_t GetPort();
    const std::string GetListenMessage();

    void Connect(ISocketWrapper& socket);
    void SetupServer(ISocketWrapper& socket);
}
