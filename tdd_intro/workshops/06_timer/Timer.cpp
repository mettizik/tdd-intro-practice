#include "Timer.h"

constexpr micloud::utils::Timer::DefaultTimePoint micloud::utils::Timer::UninitializedTimePoint()
{
    return DefaultTimePoint::min();
}

micloud::utils::Timer::DefaultTimePoint micloud::utils::Timer::CurrentTime()
{
    return DefaultClock::now();
}

bool micloud::utils::Timer::Expired() const
{
    return TimeLeft() <= DefaultDuration(0);
}

void micloud::utils::Timer::Start()
{
    m_startPoint = CurrentTime();
}

micloud::utils::Timer::DefaultDuration micloud::utils::Timer::TimeLeft() const
{
    return m_timeout - (CurrentTime() - m_startPoint);
}
