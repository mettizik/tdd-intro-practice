#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Timer.h"

/*
Implement a timer class that implements ITimer interface defined in header file ITimer.h

Followed by this specification:
    Timer allows to determine if specific period of time expired or not since Start was called last time
    Timer allows to determine how much time left till period is expired
    Timer can be started again any time, no metter in what state it is
*/

class MockSystemTime : public ISystemTime
{
public:
    MOCK_METHOD0(CurrentSystemTime, uint32_t());
    MOCK_METHOD0(SaveCurrentSystemTime, void());
    MOCK_METHOD0(GetSavedCurrentSystemTime, uint32_t());
};

TEST(Timer, Timer_Take_0)
{
    MockSystemTime mock;
    EXPECT_CALL(mock, SaveCurrentSystemTime()).Times(0);
    EXPECT_CALL(mock, GetSavedCurrentSystemTime()).Times(1);
    EXPECT_CALL(mock, CurrentSystemTime()).Times(1);

    Timer timer(mock);
    timer.Start(0);

    EXPECT_TRUE(timer.IsExpired());
}

TEST(Timer, Timer_Not_Expired)
{
    MockSystemTime mock;
    EXPECT_CALL(mock, SaveCurrentSystemTime()).Times(1);
    EXPECT_CALL(mock, GetSavedCurrentSystemTime()).Times(1).WillOnce(::testing::Return(12));
    EXPECT_CALL(mock, CurrentSystemTime()).Times(1).WillOnce(::testing::Return(1011));

    Timer timer(mock);
    timer.Start(1000);

    EXPECT_FALSE(timer.IsExpired());
}

TEST(Timer, Timer_Expired)
{
    MockSystemTime mock;

    EXPECT_CALL(mock, SaveCurrentSystemTime()).Times(1);
    EXPECT_CALL(mock, GetSavedCurrentSystemTime()).Times(1).WillOnce(::testing::Return(12));
    EXPECT_CALL(mock, CurrentSystemTime()).Times(1).WillOnce(::testing::Return(1012));

    Timer timer(mock);
    timer.Start(1000);
    EXPECT_TRUE(timer.IsExpired());
}

TEST(Timer, Timer_TimeLeft_Return_0)
{
    MockSystemTime mock;

    EXPECT_CALL(mock, SaveCurrentSystemTime()).Times(0);
    EXPECT_CALL(mock, GetSavedCurrentSystemTime()).Times(2);
    EXPECT_CALL(mock, CurrentSystemTime()).Times(2);

    Timer timer(mock);
    timer.Start(0);
    EXPECT_TRUE(timer.IsExpired());
    EXPECT_EQ(Duration(0), timer.TimeLeft());
}

TEST(Timer, Timer_TimeLeft_Return_900)
{
    MockSystemTime mock;

    EXPECT_CALL(mock, SaveCurrentSystemTime()).Times(1);
    EXPECT_CALL(mock, GetSavedCurrentSystemTime()).Times(2).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(mock, CurrentSystemTime()).Times(2).WillRepeatedly(::testing::Return(101));

    Timer timer(mock);
    timer.Start(1000);
    EXPECT_FALSE(timer.IsExpired());
    EXPECT_EQ(Duration(900), timer.TimeLeft());
}

TEST(Timer, Timer_TimeLeft_Expired_And_Return_0)
{
    MockSystemTime mock;

    EXPECT_CALL(mock, SaveCurrentSystemTime()).Times(1);
    EXPECT_CALL(mock, GetSavedCurrentSystemTime()).Times(2).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(mock, CurrentSystemTime()).Times(2).WillRepeatedly(::testing::Return(1001));

    Timer timer(mock);
    timer.Start(1000);
    EXPECT_TRUE(timer.IsExpired());
    EXPECT_EQ(Duration(0), timer.TimeLeft());
}


TEST(Timer, Timer_TimeLeft_Return_900_Start_Return_999)
{
    MockSystemTime mock;

    EXPECT_CALL(mock, SaveCurrentSystemTime()).Times(2);
    EXPECT_CALL(mock, GetSavedCurrentSystemTime()).Times(4).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(mock, CurrentSystemTime()).Times(4).WillOnce(::testing::Return(101))
                                                   .WillOnce(::testing::Return(101))
                                                   .WillOnce(::testing::Return(2))
                                                   .WillOnce(::testing::Return(2));

    Timer timer(mock);
    timer.Start(1000);
    EXPECT_FALSE(timer.IsExpired());
    EXPECT_EQ(Duration(900), timer.TimeLeft());

    timer.Start(1000);
    EXPECT_FALSE(timer.IsExpired());
    EXPECT_EQ(Duration(999), timer.TimeLeft());
}
