#pragma once
#include <memory>
#include <string>
#include "ISocketWrapper.h"
#include "ChatSessionBase.h"

class IGui;

class ServerSession : public ChatSessionBase
{
public:
    ServerSession(ISocketWrapper::SockPtr socket);
    ServerSession(ISocketWrapper& socket);

    virtual void PerformHandshake(const std::string& nickname) override;
};
