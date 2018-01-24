#pragma once
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class Timer
{
  public:
    void Start();
    bool IsExpired() const;
    Duration TimeLeft() const;
};
