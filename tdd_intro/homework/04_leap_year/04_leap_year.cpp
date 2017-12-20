#include <gtest/gtest.h>

bool IsLeapYear(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }
    if (year % 100 == 0)
    {
        return false;
    }
    return year % 4 == 0;
}

TEST(LeapYear, IsLeapYear_returns_true_for_years_divisible_by_4)
{
    EXPECT_TRUE(IsLeapYear(1944));
    EXPECT_TRUE(IsLeapYear(880));
    EXPECT_TRUE(IsLeapYear(2016));
}

TEST(LeapYear, IsLeapYear_returns_false_for_years_not_divisible_by_4)
{
    EXPECT_FALSE(IsLeapYear(1943));
    EXPECT_FALSE(IsLeapYear(881));
    EXPECT_FALSE(IsLeapYear(2018));
}

TEST(LeapYear, IsLeapYear_returns_false_for_years_divisible_by_100)
{
    EXPECT_FALSE(IsLeapYear(100));
    EXPECT_FALSE(IsLeapYear(900));
    EXPECT_FALSE(IsLeapYear(2200));
}

TEST(LeapYear, IsLeapYear_returns_true_for_years_divisible_by_400)
{
    EXPECT_TRUE(IsLeapYear(400));
    EXPECT_TRUE(IsLeapYear(800));
    EXPECT_TRUE(IsLeapYear(2400));
}
