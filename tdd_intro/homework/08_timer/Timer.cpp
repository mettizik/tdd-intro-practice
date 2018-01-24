#include "Timer.h"

void Timer::Start(TimePoint now, Duration duration)
{
    m_start = now;
    m_duration = duration;
}

bool Timer::IsExpired(TimePoint now) const
{
    return false;
}

Duration Timer::TimeLeft() const
{
    return Duration();
}
