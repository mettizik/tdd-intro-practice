#pragma once
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class ITimer
{
  public:
    virtual ~ITimer() {}

    virtual void Start() = 0;
    virtual bool IsExpired() const = 0;
    virtual Duration TimeLeft() const = 0;
};
