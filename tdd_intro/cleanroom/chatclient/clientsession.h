#pragma once
#include <string>
#include "ISocketWrapper.h"
#include "ChatSessionBase.h"

class IGui;

class ClientSession : public ChatSessionBase
{
public:
    ClientSession(ISocketWrapper::SockPtr socket);

    virtual std::string PerformHandshake(const std::string& nickname) override;
};
