#include "Timer.h"

Timer::Timer(ISystemTime& systemTime)
    : m_systemTime(systemTime)
    , m_msec(0)
{
}

void Timer::Start(uint32_t msec)
{
    if (msec == 0)
    {
        return;
    }
    m_systemTime.SaveCurrentSystemTime();
    m_msec = msec;
}

bool Timer::IsExpired() const
{
    return GetDiffCurrentAndSavedTime() >= m_msec;
}

Duration Timer::TimeLeft() const
{
    return Duration(m_msec - GetDiffCurrentAndSavedTime());
}

uint32_t Timer::GetDiffCurrentAndSavedTime() const
{
    return m_systemTime.CurrentSystemTime() - m_systemTime.GetSavedCurrentSystemTime();
}
