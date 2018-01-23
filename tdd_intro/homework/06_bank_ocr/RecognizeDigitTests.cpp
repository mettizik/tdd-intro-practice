#include <gtest/gtest.h>
#include "BankOcr.h"

TEST(BankOcr, RecognizeDigit_recognizes_digit_one)
{
    EXPECT_EQ(1, BankOcr::detail::RecognizeDigit("   ",
                                                 "  |",
                                                 "  |"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_two)
{
    EXPECT_EQ(2, BankOcr::detail::RecognizeDigit(" _ ",
                                                 " _|",
                                                 "|_ "));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_three)
{
    EXPECT_EQ(3, BankOcr::detail::RecognizeDigit(" _ ",
                                                 " _|",
                                                 " _|"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_four)
{
    EXPECT_EQ(4, BankOcr::detail::RecognizeDigit("   ",
                                                 "|_|",
                                                 "  |"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_five)
{
    EXPECT_EQ(5, BankOcr::detail::RecognizeDigit(" _ ",
                                                 "|_ ",
                                                 " _|"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_six)
{
    EXPECT_EQ(6, BankOcr::detail::RecognizeDigit(" _ ",
                                                 "|_ ",
                                                 "|_|"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_seven)
{
    EXPECT_EQ(7, BankOcr::detail::RecognizeDigit(" _ ",
                                                 "  |",
                                                 "  |"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_eight)
{
    EXPECT_EQ(8, BankOcr::detail::RecognizeDigit(" _ ",
                                                 "|_|",
                                                 "|_|"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_nine)
{
    EXPECT_EQ(9, BankOcr::detail::RecognizeDigit(" _ ",
                                                 "|_|",
                                                 " _|"));
}
