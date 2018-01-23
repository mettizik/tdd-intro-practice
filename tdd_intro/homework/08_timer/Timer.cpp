#include "Timer.h"

Timer::Timer(Duration duration)
    : m_duration(duration)
{
}

void Timer::Start(TimeLambda& currentTime)
{
    m_startPoint = currentTime();
}

bool Timer::IsExpired(TimeLambda& currentTime) const
{
    TimePoint currenPoint = currentTime();
    return (m_duration + m_startPoint) <= currenPoint;
}

Duration Timer::TimeLeft(TimeLambda& currentTime) const
{
    return m_duration - (currentTime() - m_startPoint);
}
