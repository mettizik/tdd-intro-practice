#include "Timer.h"

Timer::Timer(Duration duration)
    : m_duration(duration)
{
}

void Timer::Start(TimeLambda& currentTime)
{
}

bool Timer::IsExpired(TimeLambda& currentTime) const
{
    return false;
}

Duration Timer::TimeLeft(TimeLambda& currentTime) const
{
    return Duration(0);
}
