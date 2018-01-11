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
}

int Parse(const Lines& lines)
{
    if (!lines.empty())
    {
        return 1;
    }
    return 0;
}

TEST(Bank, EmptyStrings)
{
    Lines lines;
    EXPECT_EQ(Parse(lines), 0);
}

TEST(Bank, InvalidStingCount)
{
    Lines lines;
    lines.push_back(one_top);
    lines.push_back(one_mid);
    lines.push_back(one_bottom);

    EXPECT_EQ(Parse(lines), 1);
}
