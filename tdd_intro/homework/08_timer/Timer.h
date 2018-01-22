#pragma once
#include "ITimer.h"

class Timer : public ITimer
{
  public:
    virtual void Start() override;
    virtual bool IsExpired() const override;
    virtual Duration TimeLeft() const override;
};
