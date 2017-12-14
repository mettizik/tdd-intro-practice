#include <gtest/gtest.h>
#include <sstream>

// 3 = Fizz
// 5 = Buzz
// 15 = FizzBuzz

std::string fizzbuzz(size_t i)
{
    std::string val;
    if (i % 3 == 0)
    {
        val += "Fizz";
    }
    if (i % 5 == 0)
    {
        val += "Buzz";
    }
    return val.empty() ? std::to_string(i) : val;
}

TEST(FizzBuzz, fizz_buzz_returns_one_when_receives_one)
{
    EXPECT_EQ("1", fizzbuzz(1));
}

TEST(FizzBuzz, fizz_buzz_returns_two_when_receives_two)
{
    EXPECT_EQ("2", fizzbuzz(2));
}

TEST(FizzBuzz, FizzBuzz_fizz_buzz_returns_fizz_when_receives_number_devidable_by_three)
{
    EXPECT_EQ("Fizz", fizzbuzz(3));
    EXPECT_EQ("Fizz", fizzbuzz(6));
    EXPECT_EQ("Fizz", fizzbuzz(99));
}

TEST(FizzBuzz, FizzBuzz_returns_buzz_when_receives_number_devidable_by_five)
{
    EXPECT_EQ("Buzz", fizzbuzz(5));
    EXPECT_EQ("Buzz", fizzbuzz(10));
    EXPECT_EQ("Buzz", fizzbuzz(200));
}

TEST(FizzBuzz, FizzBuzz_returns_FizzBuzz_when_receives_number_devidable_by_five_and_three)
{
    EXPECT_EQ("FizzBuzz", fizzbuzz(15));
    EXPECT_EQ("FizzBuzz", fizzbuzz(30));
    EXPECT_EQ("FizzBuzz", fizzbuzz(600));
}
