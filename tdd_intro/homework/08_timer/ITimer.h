#pragma once
#include <chrono>
#include <functional>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;
using TimeLambda = std::function<TimePoint(void)>;

class ITimer
{
  public:
    virtual ~ITimer() {}

    virtual void Start(TimeLambda& currentTime) = 0;
    virtual bool IsExpired(TimeLambda& currentTime) const = 0;
    virtual Duration TimeLeft(TimeLambda& currentTime) const = 0;
};
