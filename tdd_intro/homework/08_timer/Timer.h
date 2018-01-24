#pragma once
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class Timer
{
public:
    void Start(TimePoint now, Duration duration);
    bool IsExpired(TimePoint now) const;
    Duration TimeLeft() const;

private:
    TimePoint m_start;
    Duration m_duration;
};
