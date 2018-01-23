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
    TimePoint currentPoint = currentTime();
    return (m_duration + m_startPoint) <= currentPoint;
}

Duration Timer::TimeLeft(const TimeLambda& currentTime) const
{
    Duration ret{0};
    if (!IsExpired(currentTime))
    {
        ret = m_duration - (currentTime() - m_startPoint);
    }
    return ret;
}
