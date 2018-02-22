#pragma once
#include <string>
#include "IChatSession.h"
#include "ISocketWrapper.h"

class IGui;

class ChatSessionBase : public IChatSession
{
public:
    ChatSessionBase(ISocketWrapper& socket, IGui& gui, const std::string& nickName);

protected:
    ISocketWrapper::SockPtr m_socket;

private:
    IGui& m_gui;
    const std::string m_nick;
};
