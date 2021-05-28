#pragma once
#include <string>

class ISocketWrapper;
class IGui;

class ServerSession
{
    public:
        ServerSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName);
};

