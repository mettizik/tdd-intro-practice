#pragma once
#include "ITimer.h"

class Timer : public ITimer
{
public:
    explicit Timer(Duration duration);

    virtual void Start(TimeLambda& currentTime) override;
    virtual bool IsExpired(TimeLambda& currentTime) const override;
    virtual Duration TimeLeft(TimeLambda& currentTime) const override;

private:
    Duration m_duration;
    TimePoint m_startPoint;
};
