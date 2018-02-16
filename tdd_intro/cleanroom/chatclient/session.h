#pragma once
#include <string>

class ISocketWrapper;
class IGui;

class Session
{
    public:
        Session(ISocketWrapper& socket, IGui& gui, const std::string& nickName);
};

class ClientSession
{
    public:
        ClientSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName);
};
