/*
Write a function, that is given a string and a length limit,
splits provided string into sequence of string,
where length of each string is not more, than provided limit.
If there are spaces under provided limit - last space should
 be used to wrapp this line. If there are no spaces - wrapp
it on provided length limit.
*/

#include <gtest/gtest.h>
#include <string>
#include <list>

using ListOfStrings = std::list<std::string>;

ListOfStrings WordWrapp(const std::string& line, size_t limit)
{
    if (line.length() <= limit)
    {
        return ListOfStrings{line};
    }
    return ListOfStrings{""};
}

TEST(WordWrapp, WordWrapp_returns_empty_line_on_empty_input_string)
{
    EXPECT_EQ(ListOfStrings{""}, WordWrapp("", 0));
}

TEST(WordWrapp, WordWrapp_returns_string_if_it_shorter_then_limit)
{
    EXPECT_EQ(ListOfStrings{"string"}, WordWrapp("string", INT_LEAST64_MAX));
}
