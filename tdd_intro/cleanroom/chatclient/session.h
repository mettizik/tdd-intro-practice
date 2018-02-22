#pragma once
#include <string>

class ISocketWrapper;
class IGui;

class Session
{
    public:
        Session(ISocketWrapper& socket, IGui& gui, const std::string& nickName);
};
