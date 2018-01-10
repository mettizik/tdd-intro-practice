#include <gtest/gtest.h>

int RecognizeDigit(const std::string& line1, const std::string& line2, const std::string& line3)
{
    return 1;
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_one)
{
    EXPECT_EQ(1, RecognizeDigit("  |",
                                "  |",
                                "  |"));
}
