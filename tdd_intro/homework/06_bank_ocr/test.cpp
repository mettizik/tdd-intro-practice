#include <gtest/gtest.h>

/*
 * Tests list:
 * - parse a digit from a square 3x9
 * - parse an account number (9 digits)
 * - parse a wrong digit (not in the range 0-9)
 * - parse several account numbers (500:)
 */

using Lines = std::vector<std::string>;

std::string ParseAccountNumbers(const Lines& lines)
{

    return lines.front()[1] == ' '
            ? "1"
            : lines.back().front() == ' ' ? "3" : "2";
}

TEST(ParseAccountNumbers, Take_one_Returns_1)
{
    EXPECT_EQ("1", ParseAccountNumbers({
                                           "   ",
                                           "  |",
                                           "  |"
                                       }));
}

TEST(ParseAccountNumbers, Take_two_Returns_2)
{
    EXPECT_EQ("2", ParseAccountNumbers({
                                           " _ ",
                                           " _|",
                                           "|_ "
                                       }));
}

TEST(ParseAccountNumbers, Take_three_Returns_3)
{
    EXPECT_EQ("3", ParseAccountNumbers({
                                           " _ ",
                                           " _|",
                                           " _|"
                                       }));
}
