/*
### Word Wrapp

Write a function, that is given a string and a length limit, splits provided string into sequence of string,
where length of each string is not more, than provided limit.
If there are spaces under provided limit - last space should be used to wrapp this line.
If there are no spaces - wrapp it on provided length limit.

As an acceptance test you can use this input:
```
When pos is specified, the search only includes sequences of characters that begin at or before position pos, ignoring any possible match beginning after pos.
```
It should be wrapped by length of 30 into this sequence of lines (ommiting quotes):
```
"When pos is specified, the",
"search only includes sequences",
"of characters that begin at or",
"before position pos, ignoring",
"any possible match beginning",
"after pos."
```*/

#include <gtest/gtest.h>
#include <sstream>

using Lines = std::vector<std::string>;

Lines WordWrap(const std::string& text, const unsigned maxLineLen)
{
    if (maxLineLen == 0 || text.empty() || text.length() <= maxLineLen)
    {
        return {text};
    }

    Lines lines;
    size_t lineLen = maxLineLen;
    for (size_t startPos = 0; startPos < text.length(); startPos += lineLen)
    {
        std::string line = text.substr(startPos, maxLineLen);
        bool isSpaceAfterLine = (text[startPos + line.length()] == ' ');
        lines.push_back(isSpaceAfterLine ? line : line.substr(0, line.rfind(' ')));
        lineLen = lines.back().length();
        bool isWrappedBySpace = (lineLen != maxLineLen);
        startPos += (isSpaceAfterLine || isWrappedBySpace) ? 1 : 0;
    }
    return lines;
}

TEST(WordWrap, Take_empty_string_Return_empty)
{
    EXPECT_EQ(Lines({""}), WordWrap("", 10));
}

TEST(WordWrap, Take_string_and_zero_limit_Return_this_string)
{
    EXPECT_EQ(Lines({"hello world"}), WordWrap("hello world", 0));
}

TEST(WordWrap, Take_string_without_spaces_Return_2_strings_splitted_by_length_limit)
{
    EXPECT_EQ(Lines({"hello", "world"}), WordWrap("helloworld", 5));
}

TEST(WordWrap, Take_string_without_spaces_Return_3_strings_splitted_by_length_limit)
{
    EXPECT_EQ(Lines({"hello", "world", "hello"}), WordWrap("helloworldhello", 5));
}

TEST(WordWrap, Take_string_with_1_space_Return_2_strings_splitted_by_space)
{
    EXPECT_EQ(Lines({"hell", "world"}), WordWrap("hell world", 6));
}

TEST(WordWrap, Take_string_with_2_spaces_Return_3_strings_splitted_by_space)
{
    EXPECT_EQ(Lines({"it", "is", "cat"}), WordWrap("it is cat", 4));
}

TEST(WordWrap, Take_string_with_space_and_big_limit_Return_this_line)
{
    EXPECT_EQ(Lines({"it is"}), WordWrap("it is", 5));
    EXPECT_EQ(Lines({"it is"}), WordWrap("it is", 6));
}

TEST(WordWrap, Take_string_with_space_at_once_after_limit_Return_2_lines)
{
    EXPECT_EQ(Lines({"it is", "cat"}), WordWrap("it is cat", 5));
}
