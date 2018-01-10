#include <gtest/gtest.h>

namespace
{
    bool EndsWith(const std::string& input, char suffix)
    {
        return input.find_last_of(suffix) == (input.size() - 1);
    }
}

std::string Bob(const std::string& input)
{
    if (input.empty())
    {
        return "Fine. Be that way!";
    }
    if (EndsWith(input, '?'))
    {
        return "Sure.";
    }
    if (EndsWith(input, '!'))
    {
        return "Whoa, chill out!";
    }
    return "Whatever.";
}

TEST(Bob, Retuns_Sure_when_input_ends_with_question_mark)
{
    EXPECT_EQ(Bob("What? Why?"), "Sure.");
}

TEST(Bob, Retuns_Whoachillout_when_input_ends_with_exclamation_mark)
{
    EXPECT_EQ(Bob("Stop! Now!"), "Whoa, chill out!");
}

TEST(Bob, Retuns_FineBethatway_when_input_is_empty)
{
    EXPECT_EQ(Bob(""), "Fine. Be that way!");
}

TEST(Bob, Retuns_Whatever_otherwise)
{
    EXPECT_EQ(Bob("? cool ! yo"), "Whatever.");
}
