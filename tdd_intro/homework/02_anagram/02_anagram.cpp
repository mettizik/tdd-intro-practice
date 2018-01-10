#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>
#include <functional>

using WordList_vt = std::vector<std::string>;

bool IsAnagram(const std::string& first, const std::string& second)
{
    return first.size() == second.size() && std::is_permutation(first.begin(), first.end(), second.begin());
}

WordList_vt KeepAnagrams(const std::string& word, const WordList_vt& candidates)
{
    WordList_vt result;
    const auto isAnagramToWord = [&word](const std::string& candidate){ return IsAnagram(word, candidate); };
    std::copy_if(candidates.begin(), candidates.end(), std::back_inserter(result), isAnagramToWord);
    return result;
}

TEST(Anagram, IsAnagram_returns_true_if_inputs_are_anagram)
{
    EXPECT_TRUE(IsAnagram("listen", "inlets"));
}

TEST(Anagram, IsAnagram_returns_false_if_inputs_are_not_anagram)
{
    EXPECT_FALSE(IsAnagram("listen", "enlists"));
    EXPECT_FALSE(IsAnagram("listen", "google"));
    EXPECT_FALSE(IsAnagram("listen", "banana"));
}

TEST(Anagram, KeepAnagrams_returns_list_containing_only_anagrams)
{
    const std::string word{"listen"};
    const WordList_vt candidates{"enlists", "google", "inlets", "banana"};
    const WordList_vt anagrams = KeepAnagrams(word, candidates);
    const auto isAnagramToWord = [&word](const std::string& candidate){ return IsAnagram(word, candidate); };
    EXPECT_THAT(anagrams, testing::Each(testing::Truly(isAnagramToWord)));
    EXPECT_THAT(anagrams, testing::Contains("inlets"));
}
