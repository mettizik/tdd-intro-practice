/*
Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4 except every year that is evenly divisible by 100 unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>

bool IsLeap(int year)
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

TEST(IsLeap, IsLeap_returns_false_on_non_devided_by_4)
{
    EXPECT_FALSE(IsLeap(3));
    EXPECT_FALSE(IsLeap(15));
    EXPECT_FALSE(IsLeap(101));
    EXPECT_FALSE(IsLeap(2001));
}

TEST(IsLeap, IsLeap_returns_true_on_devided_by_4)
{
    EXPECT_TRUE(IsLeap(4));
    EXPECT_TRUE(IsLeap(16));
    EXPECT_TRUE(IsLeap(104));
    EXPECT_TRUE(IsLeap(2004));
}

TEST(IsLeap, IsLeap_returns_false_on_devided_by_100)
{
    EXPECT_FALSE(IsLeap(100));
    EXPECT_FALSE(IsLeap(200));
    EXPECT_FALSE(IsLeap(500));
    EXPECT_FALSE(IsLeap(2100));
}

TEST(IsLeap, IsLeap_returns_true_on_devided_by_400)
{
    EXPECT_TRUE(IsLeap(400));
    EXPECT_TRUE(IsLeap(800));
    EXPECT_TRUE(IsLeap(2000));
}
