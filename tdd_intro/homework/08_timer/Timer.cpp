#include "Timer.h"

bool Timer::Expired() const
{
    return false;
}

void Timer::Start()
{
}

DefaultDuration Timer::TimeLeft() const
{
    return DefaultDuration();
}
