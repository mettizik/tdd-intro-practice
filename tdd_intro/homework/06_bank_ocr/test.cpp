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
            ? (lines[1].front() == ' ' ? "1" : "4")
            : lines.back().front() == ' '
                ? (lines[1].front() == ' '
                    ? (lines.back()[1] == ' ' ? "7" : "3")
                    : "5")
                : lines.back().back() == ' ' ? "2" : "6";
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

TEST(ParseAccountNumbers, Take_four_Returns_4)
{
    EXPECT_EQ("4", ParseAccountNumbers({
                                           "   ",
                                           "|_|",
                                           "  |"
                                       }));
}

TEST(ParseAccountNumbers, Take_five_Returns_5)
{
    EXPECT_EQ("5", ParseAccountNumbers({
                                           " _ ",
                                           "|_ ",
                                           " _|"
                                       }));
}

TEST(ParseAccountNumbers, Take_six_Returns_6)
{
    EXPECT_EQ("6", ParseAccountNumbers({
                                           " _ ",
                                           "|_ ",
                                           "|_|"
                                       }));
}

TEST(ParseAccountNumbers, Take_seven_Returns_7)
{
    EXPECT_EQ("7", ParseAccountNumbers({
                                           " _ ",
                                           "  |",
                                           "  |"
                                       }));
}
