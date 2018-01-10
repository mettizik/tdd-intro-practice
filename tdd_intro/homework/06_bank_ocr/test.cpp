#include <gtest/gtest.h>

int RecognizeDigit(const std::string& line1, const std::string& line2, const std::string& line3)
{
    if      (line1 == "   " && line2 == "  |" && line3 == "  |")
    {
        return 1;
    }
    else if (line1 == " _ " && line2 == " _|" && line3 == "|_ ")
    {
        return 2;
    }
    else if (line1 == " _ " && line2 == " _|" && line3 == " _|")
    {
        return 3;
    }
    else if (line1 == "   " && line2 == "|_|" && line3 == "  |")
    {
        return 4;
    }
    else if (line1 == " _ " && line2 == "|_ " && line3 == " _|")
    {
        return 5;
    }
    else if (line1 == " _ " && line2 == "|_ " && line3 == "|_|")
    {
        return 6;
    }
    else if (line1 == " _ " && line2 == "  |" && line3 == "  |")
    {
        return 7;
    }
    else if (line1 == " _ " && line2 == "|_|" && line3 == "|_|")
    {
        return 8;
    }
    else if (line1 == " _ " && line2 == "|_|" && line3 == " _|")
    {
        return 9;
    }
    return 0;
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

TEST(BankOcr, RecognizeDigit_recognizes_digit_three)
{
    EXPECT_EQ(3, RecognizeDigit(" _ ",
                                " _|",
                                " _|"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_four)
{
    EXPECT_EQ(4, RecognizeDigit("   ",
                                "|_|",
                                "  |"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_five)
{
    EXPECT_EQ(5, RecognizeDigit(" _ ",
                                "|_ ",
                                " _|"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_six)
{
    EXPECT_EQ(6, RecognizeDigit(" _ ",
                                "|_ ",
                                "|_|"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_seven)
{
    EXPECT_EQ(7, RecognizeDigit(" _ ",
                                "  |",
                                "  |"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_eight)
{
    EXPECT_EQ(8, RecognizeDigit(" _ ",
                                "|_|",
                                "|_|"));
}

TEST(BankOcr, RecognizeDigit_recognizes_digit_nine)
{
    EXPECT_EQ(9, RecognizeDigit(" _ ",
                                "|_|",
                                " _|"));
}
