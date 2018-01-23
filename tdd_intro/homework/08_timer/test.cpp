#include <gtest/gtest.h>

#include "Timer.h"

/*
Implement a timer class that implements ITimer interface defined in header file ITimer.h

Followed by this specification:
    Timer allows to determine if specific period of time expired or not since Start was called last time
    Timer allows to determine how much time left till period is expired
    Timer can be started again any time, no metter in what state it is
*/

/*
   Test list:
   1. Start called and IsExpired returns false on non expired time;
   2. Start called and IsExpired returns true on expired time;
   3. Start called and TimeLeft returns duration beetwin maxTime and 1 on non expired time;
   4. Start called and TimeLeft returns 0 on expired time;
   5. Start called and after timer expires start called one more time and timer is no longer expired;
   6. Start called and before timer expires start called one more time and it is still not expired.
*/

using namespace std::chrono_literals;
namespace
{
    const TimeLambda s_oneScond = [](){return TimePoint{1s};};
    const TimeLambda s_twoSconds = [](){return TimePoint{2s};};
    const TimeLambda s_threeSeconds = [](){return TimePoint{3s};};
    const TimeLambda s_fourSeconds = [](){return TimePoint{4s};};
}

TEST(Timer, TimerNotExpiresIfFlowedTimeIsLessThanTimerWasBoundTo)
{
    Timer timer{2s};
    timer.Start(s_oneScond);
    EXPECT_FALSE(timer.IsExpired(s_twoSconds));
}

TEST(Timer, TimerExpiresIfFlowedTimeIsMoreThanTimerWasBoundTo)
{
    Timer timer{2s};
    timer.Start(s_oneScond);
    EXPECT_TRUE(timer.IsExpired(s_fourSeconds));
}

TEST(Timer, TimerExpiresIfFlowedTimeIsExectAsTimerWasBoundTo)
{
    Timer timer{2s};
    timer.Start(s_oneScond);
    EXPECT_TRUE(timer.IsExpired(s_threeSeconds));
}

TEST(Timer, TimeLeftReturnsTimeLeftForExpiring)
{
    Timer timer{10s};
    timer.Start(s_oneScond);
    Duration expectedDuration{8s};
    EXPECT_EQ(expectedDuration, timer.TimeLeft(s_threeSeconds));
}
