#include <gtest/gtest.h>

std::string TellBob(const std::string& phrase)
{
    if (phrase.empty())
    {
        return "Fine. Be that way!";
    }

    switch (phrase.back())
    {
    case '?':
        return "Sure.";
    case '!':
        return "Whoa, chill out!";
    default:
        return "Whatever.";
    }
}

TEST(Bob, anwers_sure_when_you_ask_him)
{
    EXPECT_EQ("Sure.", TellBob("What?"));
}

TEST(Bob, anwers_whoachillout_when_you_yell_at_him)
{
    EXPECT_EQ("Whoa, chill out!", TellBob("Bob!"));
}

TEST(Bob, anwers_finebethatway_when_you_say_anything)
{
    EXPECT_EQ("Fine. Be that way!", TellBob(""));
}

TEST(Bob, anwers_whatever_when_you_dont_ask_or_yell_at_him)
{
    EXPECT_EQ("Whatever.", TellBob("Say something else, Bob"));
    EXPECT_EQ("Whatever.", TellBob("Hello."));
    EXPECT_EQ("Whatever.", TellBob("You are a robot..."));
}

TEST(Bob, anwers_whatever_when_you_insert_punctuation_mark_not_in_the_end_of_sentense)
{
    EXPECT_EQ("Whatever.", TellBob("? "));
    EXPECT_EQ("Whatever.", TellBob("! "));
    EXPECT_EQ("Whatever.", TellBob(". "));
}
