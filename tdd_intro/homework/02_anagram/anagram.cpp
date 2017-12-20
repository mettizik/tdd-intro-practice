/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".
*/

#include <gtest/gtest.h>
#include <string>
#include <list>

using ListOfStrings = std::list<std::string>;

ListOfStrings GetAnnagrams(const std::string& word, const ListOfStrings& list)
{
    if (word.empty() || list.empty())
    {
        return ListOfStrings{};
    }
    return ListOfStrings{""};
}

TEST(GetAnnagrams, GetAnnagrams_returns_empty_list_on_empty_input)
{
    EXPECT_EQ(ListOfStrings{}, GetAnnagrams("", {}));
}
