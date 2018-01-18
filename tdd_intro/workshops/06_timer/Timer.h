#pragma once
#include <chrono>

namespace micloud
{
    namespace utils
    {
        class Timer
        {
        public:
            typedef std::chrono::high_resolution_clock DefaultClock;
            typedef DefaultClock::duration DefaultDuration;
            typedef std::chrono::time_point<DefaultClock> DefaultTimePoint;

            static constexpr DefaultTimePoint UninitializedTimePoint();
            static DefaultTimePoint CurrentTime();

            template <class DurationT>
            explicit Timer(DurationT timeout)
                : m_timeout(std::chrono::duration_cast<DefaultDuration>(timeout))
                , m_startPoint(decltype(m_startPoint)::min())
            {}

            bool Expired() const;
            void Start();
            DefaultDuration TimeLeft() const;

        private:
            DefaultDuration m_timeout;
            DefaultTimePoint m_startPoint;
        };
    }
}
