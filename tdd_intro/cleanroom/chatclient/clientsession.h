#pragma once
#include <string>
#include "ISocketWrapper.h"
#include "ChatSessionBase.h"

class IGui;

class ClientSession : public ChatSessionBase
{
public:
    ClientSession(ISocketWrapper::SockPtr socket);
    ClientSession(ISocketWrapper& socket);

    virtual void PerformHandshake(const std::string& nickname) override;
};
