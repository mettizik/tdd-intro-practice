#pragma once
#include "ITimer.h"

class Timer : public ITimer
{
  public:
    virtual void Start(uint32_t currentTime, uint32_t period) override;
    virtual bool IsExpired(uint32_t currentTime) const override;
    virtual Duration TimeLeft(uint32_t currentTime) const override;

    private:
        uint32_t m_finishTime;
};
