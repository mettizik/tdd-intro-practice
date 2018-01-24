#include "Timer.h"

void Timer::Start(TimePoint endTime)
{
    m_endTime = endTime;
    m_started = true;
}

bool Timer::IsExpired(TimePoint now) const
{
    return m_started && (now >= m_endTime);
}

Duration Timer::TimeLeft() const
{
    return Duration();
}
