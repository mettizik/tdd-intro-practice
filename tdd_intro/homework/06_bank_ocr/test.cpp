#include <gtest/gtest.h>

int RecognizeDigit(const std::string& line1, const std::string& line2, const std::string& line3)
{
    if (line1 == "   " && line2 == "  |" && line3 == "  |")
    {
        return 1;
    }
    else if (line1 == " _ " && line2 == " _|" && line3 == "|_ ")
    {
        return 2;
    }
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_one)
{
    EXPECT_EQ(1, RecognizeDigit("   ",
                                "  |",
                                "  |"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_two)
{
    EXPECT_EQ(2, RecognizeDigit(" _ ",
                                " _|",
                                "|_ "));
}
