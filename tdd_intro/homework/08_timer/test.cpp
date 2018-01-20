#include <gtest/gtest.h>

#include "Timer.h"

/*
Implement a timer class that implements ITimer interface defined in header file ITimer.h

Followed by this specification:
    Timer allows to determine if specific period of time expired or not since Start was called last time
    Timer allows to determine how much time left till period is expired
    Timer can be started again any time, no metter in what state it is
*/

TEST(Timer, Timer_Not_Expired)
{
    Timer timer;
    EXPECT_FALSE(timer.IsExpired());
}
