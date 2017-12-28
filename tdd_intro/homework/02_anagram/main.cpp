//Given a word and a list of possible anagrams, select the correct sublist.
//
//Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana"
//the program should return a list containing "inlets".

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

using WordsList = std::set<std::string>;

WordsList GetAnagrams(const std::string& word, const WordsList& candidates)
{
    if (word.empty() || candidates.empty())
    {
        return {};
    }
    WordsList anagrams;

    std::string sortedWord = word;
    std::sort(sortedWord.begin(), sortedWord.end());

    for (const auto& candidate : candidates)
    {
        std::string sortedCandidate = candidate;
        std::sort(sortedCandidate.begin(), sortedCandidate.end());
        if (sortedWord == sortedCandidate)
        {
            anagrams.insert(candidate);
        }
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
    EXPECT_EQ(WordsList{}, GetAnagrams("listen", {"enlists", "google"}));
}

TEST(GetAnagrams, Take_word_and_list_with_1_correct_anagram_Returns_it)
{
    EXPECT_EQ(WordsList{"inlets"}, GetAnagrams("listen", {"enlists", "googlee", "inlets"}));
}

TEST(GetAnagrams, Take_word_and_list_with_2_correct_anagram_Returns_it)
{
    EXPECT_EQ(WordsList({"snleti", "inlets"}), GetAnagrams("listen", {"enlists", "snleti", "inlets"}));
}

TEST(GetAnagrams, Take_word_and_list_with_duplicated_correct_anagrams_Returns_one)
{
    EXPECT_EQ(WordsList({"snleti"}), GetAnagrams("listen", {"snleti", "snleti"}));
}

TEST(GetAnagrams, acceptance_test)
{
    EXPECT_EQ(WordsList({"inlets"}), GetAnagrams("listen", {"enlists", "google", "inlets", "banana"}));
}
