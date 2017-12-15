/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <vector>

using Anagram_vt = std::vector<std::string>;

Anagram_vt GetAnagram(const std::string& in, const Anagram_vt& list)
{
    Anagram_vt out;
    for (const std::string& item : list)
    {
        if (item.size() == in.size() && item[0] != in[0])
        {
            bool result = true;
            for (const char ch : in)
            {
                result &= std::count(in.begin(), in.end(), ch) == std::count(item.begin(), item.end(), ch);
            }
            if (result)
            {
                out.push_back(item);
            }
        }
    }
    return out;
}

TEST(Anagram, GetAnaram_Take_One_Word_And_Empty_List_Return_Empty)
{
    Anagram_vt expected{};
    EXPECT_EQ(expected, GetAnagram("google", {}));
}

TEST(Anagram, GetAnaram_Take_One_Word_And_The_Same_Word_In_List_Return_Empty)
{
    Anagram_vt expected{};
    EXPECT_EQ(expected, GetAnagram("google", {"google"}));
}

TEST(Anagram, GetAnaram_Take_One_Word_And_One_Anagram_In_List_Return_The_One_Anagram)
{
    Anagram_vt expected{"elgoog"};
    EXPECT_EQ(expected, GetAnagram("google", {"elgoog"}));
}

TEST(Anagram, GetAnaram_Take_One_Word_And_Two_Anagrams_In_List_Return_The_Two_Anagrams)
{
    Anagram_vt expected{"elgoog", "ooggle"};
    EXPECT_EQ(expected, GetAnagram("google", {"elgoog", "ooggle"}));
}

TEST(Anagram, GetAnaram_Take_One_Word_And_One_Word_In_List_Return_The_Empty)
{
    Anagram_vt expected{};
    EXPECT_EQ(expected, GetAnagram("google", {"elgog"}));
}

TEST(Anagram, GetAnaram_Take_One_Word_And_One_Word_With_Diff_Chars_In_List_Return_Empty)
{
    Anagram_vt expected{};
    EXPECT_EQ(expected, GetAnagram("google", {"elooog"}));
}

