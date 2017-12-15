/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>

std::string GetBobAnswer(const std::string& in)
{
    if (in.empty())
    {
        return "Fine. Be that way!";
    }
    const size_t lastChIndex = in.size() - 1;
    if (in.find('?') == lastChIndex)
    {
        return "Sure.";
    }
    if (in.find('!') == lastChIndex)
    {
        return "Whoa, chill out!";
    }
    return "Whatever.";
}

TEST(Bob, GetBobAnswer_Take_Question_Char_Return_Sure)
{
    EXPECT_EQ("Sure.", GetBobAnswer("?"));
}

TEST(Bob, GetBobAnswer_Take_ExclanationPoint_And_Return_Whoa_chill_out)
{
    EXPECT_EQ("Whoa, chill out!", GetBobAnswer("!"));
}

TEST(Bob, GetBobAnswer_Take_Spaces_And_Question_Char_Return_Sure)
{
    EXPECT_EQ("Sure.", GetBobAnswer("   ?"));
}

TEST(Bob, GetBobAnswer_Take_Empty_String_Return_Fine_Be_That_Way)
{
    EXPECT_EQ("Fine. Be that way!", GetBobAnswer(""));
}

TEST(Bob, GetBobAnswer_Take_Some_String_Return_Whatever)
{
    EXPECT_EQ("Whatever.", GetBobAnswer("Something else"));
}

