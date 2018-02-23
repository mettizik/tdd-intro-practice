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

    virtual std::string PerformHandshake(const std::string& nickname) override;
};
