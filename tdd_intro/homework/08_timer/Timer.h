#pragma once
#include <chrono>

typedef std::chrono::high_resolution_clock DefaultClock;
typedef DefaultClock::duration DefaultDuration;
typedef std::chrono::time_point<DefaultClock> DefaultTimePoint;

class Timer
{
public:
    template <class DurationT>
    explicit Timer(DurationT timeout);

    void Start();
    bool Expired() const;
    DefaultDuration TimeLeft() const;
};
