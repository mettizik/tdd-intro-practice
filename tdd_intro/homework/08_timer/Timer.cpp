#include "Timer.h"

void Timer::Start(TimePoint& endTime)
{
    m_endTime = endTime;
    m_started = true;
}

bool Timer::IsExpired(TimePoint& now) const
{
    return m_started && (now >= m_endTime);
}

Duration Timer::TimeLeft(TimePoint& now) const
{
    if (!m_started)
    {
        return Duration{0};
    }

    return m_endTime - now;
}
