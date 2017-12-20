#include <gtest/gtest.h>
#include <string>
#include <vector>

typedef std::vector<std::string> Lines;

Lines SplitString(const std::string &line, size_t limit)
{
    if (limit >= line.size())
    {
        return Lines{line};
    }
    const auto spacePosition = line.rfind(' ', limit);
    const bool hasSpace = spacePosition != std::string::npos;
    const auto splitPoint = hasSpace ? spacePosition : limit;
    auto res = Lines{line.substr(0, splitPoint)};
    const auto restOfLine = line.substr(hasSpace ? splitPoint + 1 : splitPoint, std::string::npos);
    const auto rest = SplitString(restOfLine, limit);
    res.insert(res.end(), rest.cbegin(), rest.cend());
    return res;
}

//////////////////////////////////////////////////////////////////////////////

TEST(SplitString, split_empty_string_returns_empty_string_in_list)
{
    EXPECT_EQ(Lines{""}, SplitString("", 1));
}

TEST(SplitString, split_string_less_than_limit_returns_input_string)
{
    EXPECT_EQ(Lines{"test"}, SplitString("test", 5));
    EXPECT_EQ(Lines{"test"}, SplitString("test", 4));
}

TEST(SplitString, split_string_test_with_limit_2_returns_two_substrings)
{
    EXPECT_EQ((Lines{"te", "st"}), SplitString("test", 2));
}

TEST(SplitString, split_string_test_with_limit_1_returns_all_charecters_in_a_list)
{
    EXPECT_EQ((Lines{"t", "e", "s", "t"}), SplitString("test", 1));
}

TEST(SplitString, split_string_with_space_returns_two_words_splitted_on_space)
{
    EXPECT_EQ((Lines{"test", "test"}), SplitString("test test", 6));
    EXPECT_EQ((Lines{"test", "test"}), SplitString("test test", 5));
}

TEST(SplitString, split_string_with_space_returns_two_words_splitted_on_space_and_in_the_middle_of_the_word)
{
    EXPECT_EQ((Lines{"tes", "t", "tes", "t"}), SplitString("test test", 3));
}

TEST(SplitString, acceptance_test)
{
    EXPECT_EQ(
        (Lines{
            "When pos is specified, the",
            "search only includes sequences",
            "of characters that begin at or",
            "before position pos, ignoring",
            "any possible match beginning",
            "after pos."}),
        /*        |||123456789 123456789 123456789 ||| */
        SplitString("When pos is specified, the"
                    " search only includes sequences"
                    " of characters that begin at or"
                    " before position pos, ignoring"
                    " any possible match beginning"
                    " after pos.",
                    30));
}
