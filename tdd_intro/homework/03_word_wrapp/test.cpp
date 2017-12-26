/*
Write a function, that is given a string and a length limit, splits provided string into sequence of string,
where length of each string is not more, than provided limit. If there are spaces under provided limit -
last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.
*/

#include <gtest/gtest.h>
#include <cctype>

using Split_vt = std::vector<std::string>;

Split_vt SplitString(const std::string& in, size_t limit)
{
    if (limit > in.size() && in.size() != 0)
    {
        return {in};
    }
    Split_vt result;
    size_t j = 0;
    for (size_t i = limit; i > 0 && i < in.size(); i += limit)
    {
        result.push_back(in.substr(j, ::isspace(in[i - 1]) == 0 ? limit
                                                                : limit - 1));
        j = i;

        if ((i + limit) >= in.size())
        {
            result.push_back(in.substr(j));
            j = i;
        }
    }
    return result;
}

TEST(SplitString, SplitString_Take_Empty_String_And_Limit_Is_1_Return_Empty)
{
    Split_vt expected;
    EXPECT_EQ(expected, SplitString("", 1));
}

TEST(SplitString, SplitString_Take_String_And_Limit_Is_0_Return_Empty)
{
    Split_vt expected{};
    EXPECT_EQ(expected, SplitString("123", 0));
}

TEST(SplitString, SplitString_Take_String_With_Space_In_Middle_Limit_Is_1_Return_Three_Strings)
{
    Split_vt expected{"1", "", "3"};
    EXPECT_EQ(expected, SplitString("1 3", 1));
}

TEST(SplitString, SplitString_Take_String_With_Random_Spaces_Limit_Is_3_Return_Four_Strings)
{
    Split_vt expected{"1 ", " 2", "  ", "  4"};
    EXPECT_EQ(expected, SplitString("1   2      4", 3));
}

TEST(SplitString, SplitString_Take_String_Without_Space_Limit_Is_1_Return_Three_Strings)
{
    Split_vt expected{"1", "2", "3"};
    EXPECT_EQ(expected, SplitString("123", 1));
}

