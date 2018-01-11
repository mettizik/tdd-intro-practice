#include <gtest/gtest.h>

/*
 * Tests list:
 * + parse a digit from a square 3x9
 * - parse an account number (9 digits)
 * - parse a wrong digit (not in the range 0-9)
 * - parse several account numbers (500:)
 */

using Lines = std::vector<std::string>;

namespace
{
    Lines Join(const Lines& digit1, const Lines& digit2)
    {
        return {
            digit1[0] + digit2[0],
            digit1[1] + digit2[1],
            digit1[2] + digit2[2]
        };
    }

    std::pair<Lines, Lines> Split(const Lines& digits)
    {
        return
        {
            {
                digits[0].substr(0, 3),
                digits[1].substr(0, 3),
                digits[2].substr(0, 3)
            },
            {
                digits[0].substr(3, 3),
                digits[1].substr(3, 3),
                digits[2].substr(3, 3)
            }
        };
    }

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
    const auto digits = Split(lines);

    std::string result;
    for (const auto& digitAndLines : s_digitToLines)
    {
        if (digitAndLines.second == digits.first)
        {
            result += std::to_string(digitAndLines.first);
            break;
        }
    }
    if (lines.front().size() > 3)
    {
        for (const auto& digitAndLines : s_digitToLines)
        {
            if (digitAndLines.second == digits.second)
            {
                result += std::to_string(digitAndLines.first);
                break;
            }
        }
    }
    return result;
}

TEST(ParseAccountNumbers, Take_zero_Returns_0)
{
    EXPECT_EQ("0", ParseAccountNumbers(s_digitToLines[0]));
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

TEST(ParseAccountNumbers, Take_eight_Returns_8)
{
    EXPECT_EQ("8", ParseAccountNumbers(s_digitToLines[8]));
}

TEST(ParseAccountNumbers, Take_nine_Returns_9)
{
    EXPECT_EQ("9", ParseAccountNumbers(s_digitToLines[9]));
}

TEST(ParseAccountNumbers, Take_2_digits_Returns_correct_string)
{
    EXPECT_EQ("10", ParseAccountNumbers(Join(s_digitToLines[1], s_digitToLines[0])));
}
