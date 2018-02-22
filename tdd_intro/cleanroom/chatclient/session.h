#pragma once
#include <string>
#include "ISocketWrapper.h"
class IGui;

class Session
{
    public:
        Session(ISocketWrapper& socket, IGui& gui, const std::string& nickName);

    private:
        ISocketWrapper::SockPtr m_socket;
};
