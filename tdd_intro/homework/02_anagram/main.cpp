//Given a word and a list of possible anagrams, select the correct sublist.
//
//Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana"
//the program should return a list containing "inlets".

#include <gtest/gtest.h>
#include <vector>
#include <string>

using WordsList = std::vector<std::string>;

WordsList GetAnagrams(std::string word, WordsList candidates)
{
    return {};
}

TEST(GetAnagrams, Take_empty_list_and_empty_word_Returns_empty)
{
    EXPECT_EQ(WordsList{}, GetAnagrams("", {}));
}

TEST(GetAnagrams, Take_word_and_empty_list_Returns_empty)
{
    EXPECT_EQ(WordsList{}, GetAnagrams("listen", {}));
}

//TEST(GetAnagrams, Take_list_without_correct_anagrams_and_empty_word_Returns_empty)
//{
//    EXPECT_EQ(WordsList{}, GetAnagrams("", {"", ""}));
//}
