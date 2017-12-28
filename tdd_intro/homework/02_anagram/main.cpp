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

TEST(GetAnagrams, take_empty_list_returns_empty)
{
    EXPECT_EQ(WordsList{}, GetAnagrams("", {}));
}
