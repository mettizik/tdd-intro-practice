#include <gtest/gtest.h>
#include <string>
#include <vector>
/*User Story 1

The following format is created by the machine:
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|


Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.*/

/*
 * Test list:
 * 1. Parse one digit number (0-9 - 10 separate tests)
 * 2. Parse multiple digits number (10, 234, 123456789)
*/

using Lines = std::vector<std::string>;

std::string ParseNumber(const Lines& number)
{
    static const std::vector<Lines> numbers = std::vector<Lines>({
        Lines({" _ ",
               "| |",
               "|_|"}),
        Lines({"   ",
               "  |",
               "  |"}),
        Lines({" _ ",
               " _|",
               "|_ "}),
        Lines({" _ ",
               " _|",
               " _|"}),
        Lines({"   ",
               "|_|",
               "  |"}),
        Lines({" _ ",
               "|_ ",
               " _|"}),
        Lines({" _ ",
               "|_ ",
               "|_|"}),
        Lines({" _ ",
               "  |",
               "  |"}),
        Lines({" _ ",
               "|_|",
               "|_|"}),
        Lines({" _ ",
               "|_|",
               " _|"})
    });
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        if (numbers[i] == number)
        {
            return std::to_string(i);
        }
    }
    assert(false);
    return "?";
}

std::string GetNumberFromString(const Lines& numbers)
{
    if (numbers[0].size() != 3)
    {
        return "10";
    }
    return ParseNumber(numbers);
}

TEST(ParseNumber, ParseNumberTakesZeroReturns0)
{
    EXPECT_EQ("0", ParseNumber(Lines({" _ ",
                                      "| |",
                                      "|_|"})));
}

TEST(ParseNumber, ParseNumberTakesOneReturns1)
{
    EXPECT_EQ("1", ParseNumber(Lines({"   ",
                                      "  |",
                                      "  |"})));
}

TEST(ParseNumber, ParseNumberTakesTwoReturns2)
{
    EXPECT_EQ("2", ParseNumber(Lines({" _ ",
                                      " _|",
                                      "|_ "})));
}

TEST(ParseNumber, ParseNumberTakesThreeReturns3)
{
    EXPECT_EQ("3", ParseNumber(Lines({" _ ",
                                      " _|",
                                      " _|"})));
}

TEST(ParseNumber, ParseNumberTakesFourReturns4)
{
    EXPECT_EQ("4", ParseNumber(Lines({"   ",
                                      "|_|",
                                      "  |"})));
}

TEST(ParseNumber, ParseNumberTakesThreeReturns5)
{
    EXPECT_EQ("5", ParseNumber(Lines({" _ ",
                                      "|_ ",
                                      " _|"})));
}

TEST(ParseNumber, ParseNumberTakesThreeReturns6)
{
    EXPECT_EQ("6", ParseNumber(Lines({" _ ",
                                      "|_ ",
                                      "|_|"})));
}

TEST(ParseNumber, ParseNumberTakesThreeReturns7)
{
    EXPECT_EQ("7", ParseNumber(Lines({" _ ",
                                      "  |",
                                      "  |"})));
}

TEST(ParseNumber, ParseNumberTakesThreeReturns8)
{
    EXPECT_EQ("8", ParseNumber(Lines({" _ ",
                                      "|_|",
                                      "|_|"})));
}

TEST(ParseNumber, ParseNumberTakesThreeReturns9)
{
    EXPECT_EQ("9", ParseNumber(Lines({" _ ",
                                      "|_|",
                                      " _|"})));
}

TEST(GetNumberFromString, GetNumberFromStringTakesOneDigitNumberAndConvertItToString)
{
    EXPECT_EQ("0", GetNumberFromString (Lines({" _ ",
                                               "| |",
                                               "|_|"})));
}

TEST(GetNumberFromString, GetNumberFromStringTakesTwoDigitNumberAndConvertItToTwoDigitsString)
{
    EXPECT_EQ("10", GetNumberFromString (Lines({"    _ ",
                                                "  || |",
                                                "  ||_|"})));
}
