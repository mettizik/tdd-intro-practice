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

std::string ParseNumber(const Lines& /*number*/)
{
    return "0";
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
