#include <gtest/gtest.h>

//LIST
//1. Single symbol parsing
//2. 3 symbols parsing
//3. 9 symbols parsing
//4. work with file

namespace
{
    using Lines = std::vector<std::string>;
    const std::string one_top =    "   ";
    const std::string one_mid =    "  |";
    const std::string one_bottom = "  |";

    const std::string two_top =    " _ ";
    const std::string two_mid =    " _|";
    const std::string two_bottom = "|_ ";

    const std::string three_top =    " _ ";
    const std::string three_mid =    " _|";
    const std::string three_bottom = " _|";

    const std::string four_top =    "   ";
    const std::string four_mid =    "|_|";
    const std::string four_bottom = "  |";
}

int Parse(const Lines& lines)
{
    if (!lines.empty())
    {
        if (lines[0] == two_top
            && lines[1] == two_mid
            && lines[2] == two_bottom)
        {
            return 2;
        }
        else if (lines[0] == three_top
                 && lines[1] == three_mid
                 && lines[2] == three_bottom)
        {
            return 3;
        }
        else if (lines[0] == four_top
                 && lines[1] == four_mid
                 && lines[2] == four_bottom)
        {
            return 4;
        }
        return 1;
    }
    return 0;
}

TEST(Bank, EmptyStrings)
{
    Lines lines;
    EXPECT_EQ(Parse(lines), 0);
}

TEST(Bank, Single_one)
{
    Lines lines;
    lines.push_back(one_top);
    lines.push_back(one_mid);
    lines.push_back(one_bottom);

    EXPECT_EQ(Parse(lines), 1);
}

TEST(Bank, Single_two)
{
    Lines lines;
    lines.push_back(two_top);
    lines.push_back(two_mid);
    lines.push_back(two_bottom);

    EXPECT_EQ(Parse(lines), 2);
}

TEST(Bank, Single_three)
{
    Lines lines;
    lines.push_back(three_top);
    lines.push_back(three_mid);
    lines.push_back(three_bottom);

    EXPECT_EQ(Parse(lines), 3);
}

TEST(Bank, Single_four)
{
    Lines lines;
    lines.push_back(four_top);
    lines.push_back(four_mid);
    lines.push_back(four_bottom);

    EXPECT_EQ(Parse(lines), 4);
}
