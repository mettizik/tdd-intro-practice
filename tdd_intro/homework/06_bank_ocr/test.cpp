#include <gtest/gtest.h>

/*
 * Tests list:
 * + parse a digit from a square 3x9
 * + parse an account number (9 digits)
 * - parse a wrong digit (not in the range 0-9)
 * + parse several account numbers (500:)
 */

using Lines = std::vector<std::string>;
using Accounts = std::vector<Lines>;

namespace
{
    Lines Join(const std::vector<Lines>& digits)
    {
        Lines result{"","",""};

        for (const auto& digit : digits)
        {
            result[0] += digit[0];
            result[1] += digit[1];
            result[2] += digit[2];
        }

        return result;
    }

    std::vector<Lines> Split(const Lines& digits)
    {
        std::vector<Lines> result;

        size_t digitWidth = 3;
        size_t lineLen = digits.front().size();
        for (size_t pos = 0; pos < lineLen; pos += digitWidth)
        {
            result.push_back({
                                 digits[0].substr(pos, digitWidth),
                                 digits[1].substr(pos, digitWidth),
                                 digits[2].substr(pos, digitWidth)
                             });
        }

        return result;
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

    // "100500432" to account number
    Lines MakeAccountNumber(const std::string& number)
    {
        std::vector<Lines> digits;
        for (const auto& digit : number)
        {
            digits.push_back(s_digitToLines[digit - '0']);
        }
        return Join(digits);
    }
}

std::string AccountDigitToSimpleNumber(const Lines& digit)
{
    for (const auto& digitAndLines : s_digitToLines)
    {
        if (digitAndLines.second == digit)
        {
            return std::to_string(digitAndLines.first);
        }
    }
}

Lines ParseAccountNumbers(const Accounts& accounts)
{
    Lines accountNumbers;
    for (const auto& accountLines : accounts)
    {
        const auto accountDigits = Split(accountLines);

        std::string accountNumber;
        for (const auto& digit : accountDigits)
        {
            accountNumber += AccountDigitToSimpleNumber(digit);
        }

        accountNumbers.push_back(accountNumber);
    }
    return accountNumbers;
}

TEST(ParseAccountNumbers, Take_zero_Returns_0)
{
    EXPECT_EQ(Lines({"0"}), ParseAccountNumbers({s_digitToLines[0]}));
}

TEST(ParseAccountNumbers, Take_one_Returns_1)
{
    EXPECT_EQ(Lines({"1"}), ParseAccountNumbers({s_digitToLines[1]}));
}

TEST(ParseAccountNumbers, Take_two_Returns_2)
{
    EXPECT_EQ(Lines({"2"}), ParseAccountNumbers({s_digitToLines[2]}));
}

TEST(ParseAccountNumbers, Take_three_Returns_3)
{
    EXPECT_EQ(Lines({"3"}), ParseAccountNumbers({s_digitToLines[3]}));
}

TEST(ParseAccountNumbers, Take_four_Returns_4)
{
    EXPECT_EQ(Lines({"4"}), ParseAccountNumbers({s_digitToLines[4]}));
}

TEST(ParseAccountNumbers, Take_five_Returns_5)
{
    EXPECT_EQ(Lines({"5"}), ParseAccountNumbers({s_digitToLines[5]}));
}

TEST(ParseAccountNumbers, Take_six_Returns_6)
{
    EXPECT_EQ(Lines({"6"}), ParseAccountNumbers({s_digitToLines[6]}));
}

TEST(ParseAccountNumbers, Take_seven_Returns_7)
{
    EXPECT_EQ(Lines({"7"}), ParseAccountNumbers({s_digitToLines[7]}));
}

TEST(ParseAccountNumbers, Take_eight_Returns_8)
{
    EXPECT_EQ(Lines({"8"}), ParseAccountNumbers({s_digitToLines[8]}));
}

TEST(ParseAccountNumbers, Take_nine_Returns_9)
{
    EXPECT_EQ(Lines({"9"}), ParseAccountNumbers({s_digitToLines[9]}));
}

TEST(ParseAccountNumbers, Take_2_digits_Returns_correct_string)
{
    EXPECT_EQ(Lines({"10"}), ParseAccountNumbers({MakeAccountNumber("10")}));
}

TEST(ParseAccountNumbers, Take_3_digits_Returns_correct_string)
{
    EXPECT_EQ(Lines({"105"}), ParseAccountNumbers({MakeAccountNumber("105")}));
}

TEST(ParseAccountNumbers, Take_account_number_Returns_correct_string)
{

    EXPECT_EQ(Lines({"100500432"}), ParseAccountNumbers({MakeAccountNumber("100500432")}));
}

TEST(ParseAccountNumbers, Take_several_account_numbers_Returns_correct_strings)
{
    EXPECT_EQ(Lines({"111111111", "122222222", "333333333"}), ParseAccountNumbers(
                    {
                        MakeAccountNumber("111111111"),
                        MakeAccountNumber("122222222"),
                        MakeAccountNumber("333333333")
                    }
                  ));
}
