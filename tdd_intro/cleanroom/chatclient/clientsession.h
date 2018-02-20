#pragma once
#include <string>

class ISocketWrapper;
class IGui;

class ClientSession
{
    public:
        ClientSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName);
};
