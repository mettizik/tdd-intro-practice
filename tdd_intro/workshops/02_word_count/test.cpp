/*
Given a phrase, count the occurrences of each word in that phrase.

For example for the input "olly olly in come free"

olly: 2
in: 1
come: 1
free: 1

*/

#include <gtest/gtest.h>
#include <sstream>

using WordCount_mt = std::map<std::string, unsigned int>;

WordCount_mt CountWords(const std::string& input)
{
    WordCount_mt map;
    std::stringstream stream(input);
    while (std::getline(stream, word, " ") && !word.empty())
    {
        ++map[word];
    }
    return map;
}

TEST(CountWords, CountWords_Take_String_With_Single_Word_Return_Ones_For_This_Word)
{
    WordCount_mt expectedResult;
    expectedResult["olly"] = 1;
    EXPECT_EQ(expectedResult, CountWords("olly"));
}

TEST(CountWords, CountWords_Take_Empty_String_Returns_Empty)
{
    EXPECT_TRUE(CountWords("").empty());
}

TEST(CountWords, CountWords_Take_Two_Words_Return_Ones_For_Every_These_Words)
{
    WordCount_mt expected{{"olly", 1}, {"in", 1}};
    EXPECT_EQ(expected, CountWords("olly in"));
}

TEST(CountWords, CountWords_Take_Two_Same_Words_Return_Two_For_This_Word)
{
    WordCount_mt expected{{"olly", 2}};
    EXPECT_EQ(expected, CountWords("olly olly"));

}

TEST(CountWords, CountWords_Take_Several_Words_Return_Correct_Counts_Word)
{
    WordCount_mt expected{{"olly", 2}, {"in", 1}, {"come", 1}, {"free", 1}};
    EXPECT_EQ(expected, CountWords("olly olly in come free"));
}

TEST(CountWords, CountWords_Take_Several_Words_With_Space_In_End_Return_Correct_Counts_Word)
{
    WordCount_mt expected{{"olly", 2}, {"in", 1}, {"come", 1}, {"free", 1}};
    EXPECT_EQ(expected, CountWords("olly olly in come free "));
}

TEST(CountWords, CountWords_Take_Several_Words_With_Random_Spaces_Return_Correct_Word_Count)
{
    WordCount_mt expected{{"olly", 2}, {"in", 1}, {"come", 1}, {"free", 1}};
    EXPECT_EQ(expected, CountWords("            olly   olly in come free "));
}
