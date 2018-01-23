#pragma once
#include "ITimer.h"

class Timer : public ITimer
{
public:
    explicit Timer(Duration duration);

    virtual void Start(const TimeLambda& currentTime) override;
    virtual bool IsExpired(const TimeLambda& currentTime) const override;
    virtual Duration TimeLeft(const TimeLambda& currentTime) const override;

private:
    Duration m_duration;
    TimePoint m_startPoint;
};
