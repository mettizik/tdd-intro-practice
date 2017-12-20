/*
Bob is a lackadaisical teenager. In conversation, his responses are very limited.

Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.

Implement Bob!
*/
#include <gtest/gtest.h>
#include <string>

std::string GetBobsAnswer(const std::string& request)
{
    if (request.empty())
    {
        return "Fine. Be that way!";
    }
    return "Sure.";
}

TEST(GetBobsAnswer, GetBobsAnswer_Returns_Fine_On_Empty_Request)
{
    EXPECT_EQ("Fine. Be that way!", GetBobsAnswer(""));
}

TEST(GetBobsAnswer, GetBobsAnswer_Returns_Sure_On_Question)
{
    EXPECT_EQ("Sure.", GetBobsAnswer("?"));
    EXPECT_EQ("Sure.", GetBobsAnswer("What kind of person are you?"));
    EXPECT_EQ("Sure.", GetBobsAnswer("Are you crazy?"));
}
