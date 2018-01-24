#include <gtest/gtest.h>
#include "Timer.h"

/*
Implement a timer class that implements ITimer interface defined in header file ITimer.h

Followed by this specification:
    + Timer allows to determine if specific period of time expired or not since Start was called last time
    + Timer allows to determine how much time left till period is expired
    + Timer can be started again any time, no metter in what state it is
*/

using sec = std::chrono::seconds;

TEST(Timer, IsExpiredReturnsFalseWhenTimerIsNotStarted)
{
    Timer t;
    EXPECT_FALSE(t.IsExpired(Clock::now()));
}

TEST(Timer, IsExpiredReturnsFalseWhenTimerStarted)
{
    Timer t;
    t.Start(Clock::now() + sec(2));
    EXPECT_FALSE(t.IsExpired(Clock::now()));
}

TEST(Timer, IsExpiredReturnstTrueWhenTimerStarted)
{
    Timer t;
    t.Start(Clock::now() + sec(0));
    EXPECT_TRUE(t.IsExpired(Clock::now()));
}

TEST(Timer, TimeLeftReturnsZeroWhenTimerIsNotStarted)
{
    Timer t;
    EXPECT_EQ(Duration{0}, t.TimeLeft(Clock::now()));
}

TEST(Timer, TimeLeftReturnsCorrectValueWhenTimerIsStarted)
{
    Timer t;
    t.Start(Clock::now() + sec(2));
    EXPECT_EQ(sec(2), t.TimeLeft(Clock::now()));
}

TEST(Timer, TimeLeftReturnsZeroWhenTimerIsExpired)
{
    Timer t;
    t.Start(Clock::now());
    EXPECT_EQ(Duration{0}, t.TimeLeft(Clock::now()));
}

TEST(Timer, StartTimerTwiceAndExpireOnSecond)
{
    Timer t;
    t.Start(Clock::now() + sec(2));
    EXPECT_FALSE(t.IsExpired(Clock::now()));
    t.Start(Clock::now() + sec(0));
    EXPECT_TRUE(t.IsExpired(Clock::now()));
}

TEST(Timer, StartTimerThriceAndCheckTimeLeftCalls)
{
    Timer t;
    t.Start(Clock::now() + sec(2));
    EXPECT_EQ(sec(2), t.TimeLeft(Clock::now()));
    t.Start(Clock::now() + sec(0));
    EXPECT_EQ(Duration{0}, t.TimeLeft(Clock::now()));
    t.Start(Clock::now() + sec(5));
    EXPECT_EQ(sec(5), t.TimeLeft(Clock::now()));
}
