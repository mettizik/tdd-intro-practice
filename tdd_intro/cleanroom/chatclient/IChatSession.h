#pragma once
#include <memory>
#include "ISocketWrapper.h"

class IChatSession
{
public:
    virtual ~IChatSession() {}

    virtual std::string PerformHandshake(const std::string& nickname) = 0;
    virtual void SendMessage(const std::string& msg) = 0;
    virtual void ReadMessage(std::string& msg) = 0;
};

typedef std::shared_ptr<IChatSession> IChatSession_ptr;
