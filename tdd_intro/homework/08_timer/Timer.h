#pragma once
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class Timer
{
public:
    void Start(TimePoint& endTime);
    bool IsExpired(TimePoint& now) const;
    Duration TimeLeft(TimePoint& now) const;

private:
    TimePoint m_endTime;
    bool m_started = false;
};
