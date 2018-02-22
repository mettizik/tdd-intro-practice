#pragma once
#include <string>
#include "ISocketWrapper.h"
#include "IChatSession.h"

class IGui;

class ClientSession : public IChatSession
{
public:
    ClientSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName);

    virtual void PerformHandshake() override;

private:
    ISocketWrapper::SockPtr m_socket;
    IGui& m_gui;
    const std::string m_nick;
};
