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
    for (const auto& wordFromList : list)
    {
        if (wordFromList == word)
        {
            return ListOfStrings{word};
        }
    }
    return ListOfStrings{""};
}

TEST(GetAnnagrams, GetAnnagrams_returns_empty_list_on_empty_input)
{
    EXPECT_EQ(ListOfStrings{}, GetAnnagrams("", {}));
}

TEST(GetAnnagrams, GetAnnagrams_returns_list_with_word_if_it_matches_word_in_list)
{
    EXPECT_EQ(ListOfStrings{"expext"}, GetAnnagrams("expext", {"expext"}));
    EXPECT_EQ(ListOfStrings{"expext"}, GetAnnagrams("expext", {"expext", "not_so_expext"}));
}

TEST(GetAnnagrams, GetAnnagrams_returns_empty_list_on_words_not_annagrams)
{
    EXPECT_EQ(ListOfStrings{}, GetAnnagrams("expext", {"no_annagram"}));
}
