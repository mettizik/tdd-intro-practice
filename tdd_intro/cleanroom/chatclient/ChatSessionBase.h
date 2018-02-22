#pragma once
#include "IChatSession.h"
#include "ISocketWrapper.h"

class ChatSessionBase : public IChatSession
{
public:
    ChatSessionBase(ISocketWrapper::SockPtr socket)
        : m_socket(socket)
    {}

    virtual void SendMessage(const std::string& msg) override
    {
        m_socket->Write(msg);
    }

    virtual void ReadMessage(std::string& msg) override
    {
        m_socket->Read(msg);
    }

protected:
    ISocketWrapper::SockPtr m_socket;
};
