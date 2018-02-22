#pragma once
#include <memory>
#include <string>
#include "ISocketWrapper.h"
#include "IChatSession.h"

class IGui;

class ServerSession : public IChatSession
{
public:
    ServerSession(ISocketWrapper& socket, IGui& gui, const std::string& nickName);

    virtual void PerformHandshake() override;

private:
    ISocketWrapper::SockPtr m_socket;
    IGui& m_gui;
    const std::string m_nick;
};
