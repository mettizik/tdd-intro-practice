#include <gtest/gtest.h>

#include "Timer.h"

/*
Implement a timer class that implements ITimer interface defined in header file ITimer.h

Followed by this specification:
    Timer allows to determine if specific period of time expired or not since Start was called last time
    Timer allows to determine how much time left till period is expired
    Timer can be started again any time, no metter in what state it is
*/

TEST(timer, checkIsExpiredWithoutStart)
{
    Timer t;
    ASSERT_FALSE(t.IsExpired(100));
}

TEST(timer, checkIsExpired_beforeTime)
{
    Timer t;
    t.Start(100, 10);
    ASSERT_FALSE(t.IsExpired(109));
}

TEST(timer, checkIsExpired_afterTime)
{
    Timer t;
    t.Start(100, 15);
    ASSERT_TRUE(t.IsExpired(116));
}

TEST(timer, checkTimeLeft_beforeTime)
{
    Timer t;
    t.Start(100, 15);
    ASSERT_EQ(Duration(10), t.TimeLeft(105));
}

TEST(timer, checkTimeLeft_afterTime)
{
    Timer t;
    t.Start(10, 15);
    ASSERT_EQ(Duration(0), t.TimeLeft(105));
}

TEST(timer, checkTimerStart_reuse)
{
    Timer t;
    t.Start(100, 15);
    t.Start(110, 15);
    ASSERT_EQ(Duration(1), t.TimeLeft(124));
}
