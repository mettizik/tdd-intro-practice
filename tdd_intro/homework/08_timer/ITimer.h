#pragma once
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class ITimer
{
  public:
    virtual ~ITimer() {}

    virtual void Start(uint32_t currentTime, uint32_t period) = 0;
    virtual bool IsExpired(uint32_t currentTime) const = 0;
    virtual Duration TimeLeft(uint32_t currentTime) const = 0;
};
