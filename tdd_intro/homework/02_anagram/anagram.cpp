/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".
*/

#include <gtest/gtest.h>
#include <string>
#include <list>
#include <map>

using ListOfStrings = std::list<std::string>;
using MapOfChars = std::map<char, size_t>;

void CountChars(const std::string& word, MapOfChars& map)
{
    for (const auto& character : word)
    {
        ++map[character];
    }
}

ListOfStrings GetAnnagrams(const std::string& word, const ListOfStrings& list)
{
    if (word.empty() || list.empty())
    {
        return ListOfStrings{};
    }
    MapOfChars expectMap;
    CountChars(word, expectMap);
    for (const auto& wordFromList : list)
    {
        MapOfChars testedMap;
        CountChars(wordFromList, testedMap);
        if (expectMap == testedMap)
        {
            return ListOfStrings{wordFromList};
        }
    }
    return ListOfStrings{};
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

TEST(GetAnnagrams, GetAnnagrams_returns_list_with_word_from_input_list_if_it_is_annagram_to_given_word)
{
    EXPECT_EQ(ListOfStrings{"etxxpe"}, GetAnnagrams("expext", {"etxxpe"}));
}
