#include "Timer.h"

Timer::Timer(Duration duration)
    : m_duration(duration)
{
}

void Timer::Start(const TimeLambda& currentTime)
{
    m_startPoint = currentTime();
}

bool Timer::IsExpired(const TimeLambda& currentTime) const
{
    TimePoint currenPoint = currentTime();
    return (m_duration + m_startPoint) <= currenPoint;
}

Duration Timer::TimeLeft(const TimeLambda& currentTime) const
{
    return m_duration - (currentTime() - m_startPoint);
}
