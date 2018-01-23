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
    return ExpiredOn() <= currentTime();
}

Duration Timer::TimeLeft(const TimeLambda& currentTime) const
{
    Duration ret{0};
    if (!IsExpired(currentTime))
    {
        ret = ExpiredOn() - currentTime();
    }
    return ret;
}

TimePoint Timer::ExpiredOn() const
{
    return m_duration + m_startPoint;
}
