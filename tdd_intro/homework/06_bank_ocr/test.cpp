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
    return "1";
}

TEST(ParseAccountNumbers, Take_one_Returns_one)
{
    EXPECT_EQ("1", ParseAccountNumbers({
                                           "   ",
                                           "  |",
                                           "  |"
                                       }));
}
