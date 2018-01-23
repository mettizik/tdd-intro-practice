#include "Timer.h"

void Timer::Start(uint32_t currentTime, uint32_t period)
{
    m_finishTime = currentTime + period;
}

bool Timer::IsExpired(uint32_t currentTime) const
{
    return currentTime > m_finishTime;
}

Duration Timer::TimeLeft(uint32_t currentTime) const
{
    if (currentTime > m_finishTime)
    {
        return Duration(0);
    }
    return Duration(m_finishTime - currentTime);
}
