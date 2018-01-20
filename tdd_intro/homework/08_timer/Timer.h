#pragma once
#include "ITimer.h"

class ISystemTime
{
public:
    virtual ~ISystemTime() {}

    virtual uint32_t CurrentSystemTime() = 0;
    virtual void SaveCurrentSystemTime() = 0;
    virtual uint32_t GetSavedCurrentSystemTime() = 0;
};

class Timer : public ITimer
{
  public:
    explicit Timer(ISystemTime& systemTime);

    virtual void Start(uint32_t msec) override;
    virtual bool IsExpired() const override;
    virtual Duration TimeLeft() const override;

private:
    ISystemTime& m_systemTime;
    uint32_t m_msec;
};
