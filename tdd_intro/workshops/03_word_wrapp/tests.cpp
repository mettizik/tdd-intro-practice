#include <gtest/gtest.h>
#include <vector>
#include <string>

typedef std::vector<std::string> Lines;

/*
TASK:

    Write a function, that is given a string and a length limit,
    splits provided string into sequence of string,
    where length of each string is not more, than provided limit.
    If there are spaces under provided limit - last space should be used to wrapp this line.
    If there are no spaces - wrapp it on provided length limit.

  Acceptance test:
        Input line:
            "When pos is specified, the search only includes sequences of characters that begin at or before position pos, ignoring any possible match beginning after pos."

        Expected Lines:
        {
            "When pos is specified, the",
            "search only includes sequences",
            "of characters that begin at or",
            "before position pos, ignoring",
            "any possible match beginning",
            "after pos."
        }
*/

Lines WordWrap(const std::string& str, unsigned int len)
{
    Lines result;
    unsigned int tail = 0;
    unsigned int origLen = len;
    while (str.size() > tail + len)
    {
        auto spacePosition = str.rfind(' ', tail + len);
        bool spaceWasFound = spacePosition != std::string::npos;
        if (spaceWasFound && spacePosition > tail)
        {
            len = spacePosition - tail;
        }
        result.push_back(str.substr(tail, len));
        tail += len + (spaceWasFound ? 1 : 0);
        len = origLen;
    }

    result.push_back(str.substr(tail));

    return result;
}

TEST(WordWrap, WordWrap_retuns_empty_list_when_input_string_is_empty)
{
    EXPECT_EQ(WordWrap("", 80), Lines({""}));
}

TEST(WordWrap, WordWrap_input_str_shorten_than_len)
{
    EXPECT_EQ(WordWrap("123", 5), Lines{"123"});
}

TEST(WordWrap, WordWrap_retuns_two_elements_list_when_input_string_is_longer_than_limit)
{
    EXPECT_EQ(Lines({"123", "45"}), WordWrap("12345", 3));
}

TEST(WordWrap, WordWrap_retuns_list_of_elements_when_input_string_is_much_longer_than_limit)
{
    EXPECT_EQ(Lines({"123", "456", "789", "0"}), WordWrap("1234567890", 3));
}

TEST(WordWrap, WordWrap_retuns_list_of_elements_when_input_string_is_multiple_to_limit)
{
    EXPECT_EQ(Lines({"123", "456", "789"}), WordWrap("123456789", 3));
}

TEST(WordWrap, WordWrap_splits_input_string_by_space)
{
    EXPECT_EQ(Lines({"12", "345"}), WordWrap("12 345", 4));
}

TEST(WordWrap, WordWrap_splits_input_string_by_last_space)
{
    EXPECT_EQ(Lines({"1 2", "345"}), WordWrap("1 2 345", 4));
}

TEST(WordWrap, WordWrap_splits_input_string_by_spaces_several_times)
{
    EXPECT_EQ(Lines({"long", "thre", "solv"}), WordWrap("long thre solv", 6));
}

TEST(WordWrap, WordWrap_acceptance_test)
{
    EXPECT_EQ(Lines({
                        "When pos is specified, the",
                        "search only includes sequences",
                        "of characters that begin at or",
                        "before position pos, ignoring",
                        "any possible match beginning",
                        "after pos."
                    }), WordWrap("When pos is specified, the search only includes sequences of characters that begin at or before position pos, ignoring any possible match beginning after pos.", 30));
}
