#include <gtest/gtest.h>

/*
 * Tests list:
 * - parse a digit from a square 3x9
 * - parse an account number (9 digits)
 * - parse a wrong digit (not in the range 0-9)
 * - parse several account numbers (500:)
 */

using Lines = std::vector<std::string>;

namespace
{
    static std::map<unsigned, Lines> s_digitToLines =
    {
        { 0, { " _ ",
               "| |",
               "|_|" } },
        { 1, { "   ",
               "  |",
               "  |" } },
        { 2, { " _ ",
               " _|",
               "|_ " } },
        { 3, { " _ ",
               " _|",
               " _|" } },
        { 4, { "   ",
               "|_|",
               "  |" } },
        { 5, { " _ ",
               "|_ ",
               " _|" } },
        { 6, { " _ ",
               "|_ ",
               "|_|" } },
        { 7, { " _ ",
               "  |",
               "  |" } },
        { 8, { " _ ",
               "|_|",
               "|_|" } },
        { 9, { " _ ",
               "|_|",
               " _|" } },
    };
}

std::string ParseAccountNumbers(const Lines& lines)
{
    for (const auto& digitAndLines : s_digitToLines)
    {
        if (digitAndLines.second == lines)
            return std::to_string(digitAndLines.first);
    }
}

TEST(ParseAccountNumbers, Take_one_Returns_1)
{
    EXPECT_EQ("1", ParseAccountNumbers(s_digitToLines[1]));
}

TEST(ParseAccountNumbers, Take_two_Returns_2)
{
    EXPECT_EQ("2", ParseAccountNumbers(s_digitToLines[2]));
}

TEST(ParseAccountNumbers, Take_three_Returns_3)
{
    EXPECT_EQ("3", ParseAccountNumbers(s_digitToLines[3]));
}

TEST(ParseAccountNumbers, Take_four_Returns_4)
{
    EXPECT_EQ("4", ParseAccountNumbers(s_digitToLines[4]));
}

TEST(ParseAccountNumbers, Take_five_Returns_5)
{
    EXPECT_EQ("5", ParseAccountNumbers(s_digitToLines[5]));
}

TEST(ParseAccountNumbers, Take_six_Returns_6)
{
    EXPECT_EQ("6", ParseAccountNumbers(s_digitToLines[6]));
}

TEST(ParseAccountNumbers, Take_seven_Returns_7)
{
    EXPECT_EQ("7", ParseAccountNumbers(s_digitToLines[7]));
}
