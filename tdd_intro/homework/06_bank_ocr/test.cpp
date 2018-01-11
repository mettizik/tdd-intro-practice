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
