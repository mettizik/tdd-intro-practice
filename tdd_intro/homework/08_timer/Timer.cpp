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
    if (m_msec == 0)
    {
        return false;
    }
    return m_systemTime.CurrentSystemTime() - m_systemTime.GetSavedCurrentSystemTime() >= m_msec;
}

Duration Timer::TimeLeft() const
{
    return Duration(0);
}