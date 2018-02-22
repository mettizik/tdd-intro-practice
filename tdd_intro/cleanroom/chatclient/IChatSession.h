#pragma once
#include <memory>
#include "ISocketWrapper.h"

class IChatSession
{
public:
    virtual ~IChatSession() {}

    virtual void PerformHandshake() = 0;
};

typedef std::shared_ptr<IChatSession> IChatSession_ptr;
