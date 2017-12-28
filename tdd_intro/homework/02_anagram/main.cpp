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
    if (word.empty() || candidates.empty())
    {
        return {};
    }

    WordsList anagrams;

    auto& anagramIt = candidates.begin();
    while (true)
    {
        anagramIt = std::find_if(anagramIt, candidates.end(), [&word](const std::string& anagramCandidate)
        {
            return anagramCandidate.length() == word.length();
        });
        if (anagramIt == candidates.end())
        {
            break;
        }
        anagrams.push_back(*anagramIt);
        ++anagramIt;
    }

    return anagrams;
}

TEST(GetAnagrams, Take_empty_list_and_empty_word_Returns_empty)
{
    EXPECT_EQ(WordsList{}, GetAnagrams("", {}));
}

TEST(GetAnagrams, Take_word_and_empty_list_Returns_empty)
{
    EXPECT_EQ(WordsList{}, GetAnagrams("listen", {}));
}

TEST(GetAnagrams, Take_list_and_empty_word_Returns_empty)
{
    EXPECT_EQ(WordsList{}, GetAnagrams("", {"enlists", "google"}));
}

TEST(GetAnagrams, Take_word_and_list_without_correct_anagrams_Returns_empty)
{
    EXPECT_EQ(WordsList{}, GetAnagrams("listen", {"enlists", "googlee"}));
}

TEST(GetAnagrams, Take_word_and_list_with_1_correct_anagram_Returns_it)
{
    EXPECT_EQ(WordsList{"inlets"}, GetAnagrams("listen", {"enlists", "googlee", "inlets"}));
}

TEST(GetAnagrams, Take_word_and_list_with_2_correct_anagram_Returns_it)
{
    EXPECT_EQ(WordsList({"snleti", "inlets"}), GetAnagrams("listen", {"enlists", "snleti", "inlets"}));
}
