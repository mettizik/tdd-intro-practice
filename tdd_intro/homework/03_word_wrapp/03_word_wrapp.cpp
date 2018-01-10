#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <numeric>

using StringList_vt = std::vector<std::string>;

StringList_vt WordWrap(const std::string& input, size_t sizeLimit)
{
    StringList_vt result;
    size_t size = input.size();
    size_t offset = 0;
    while (size > sizeLimit)
    {
        std::string segment = input.substr(offset, sizeLimit);
        const size_t lastSpacePosition = segment.find_last_of(' ');
        if (lastSpacePosition != std::string::npos)
        {
            segment.resize(lastSpacePosition + 1);
        }
        result.push_back(segment);
        offset += segment.size();
        size -= segment.size();
    }
    result.push_back(input.substr(offset, size));
    return result;
}

TEST(WordWrap, WordWrap_returns_list_with_only_original_string_when_limit_is_not_reached)
{
    const std::string inputString{"Some test string of moderate length"};
    const size_t sizeLimit = 80;
    ASSERT_LE(inputString.size(), sizeLimit);
    EXPECT_THAT(WordWrap(inputString, sizeLimit), testing::ElementsAre(inputString));
}

TEST(WordWrap, WordWrap_returns_list_with_all_segments_of_limit_size_except_last)
{
    const std::string inputString{"VeryLongTestStringWithoutSpacesVeryLongTestStringWithoutSpaces"};
    const size_t sizeLimit = 17;
    ASSERT_GT(inputString.size(), sizeLimit);
    const StringList_vt wrappedList = WordWrap(inputString, sizeLimit);

    const size_t segmentCount = wrappedList.size();
    for (size_t i = 0; i < segmentCount - 1; ++i)
    {
        EXPECT_EQ(wrappedList[i].size(), sizeLimit);
    }
    EXPECT_LE(wrappedList[segmentCount - 1].size(), sizeLimit);
}

TEST(WordWrap, WordWrap_returns_list_with_all_segments_except_last_ending_with_spaces)
{
    const std::string inputString{"Very long test string with spaces. Very long test string with spaces."};
    const size_t sizeLimit = 17;
    ASSERT_GT(inputString.size(), sizeLimit);
    const StringList_vt wrappedList = WordWrap(inputString, sizeLimit);

    const size_t segmentCount = wrappedList.size();
    for (size_t i = 0; i < segmentCount - 1; ++i)
    {
        EXPECT_LE(wrappedList[i].size(), sizeLimit);
        EXPECT_THAT(wrappedList[i], testing::EndsWith(" "));
    }
}

TEST(WordWrap, WordWrap_returns_list_what_after_concatenation_equals_to_input)
{
    const std::string inputString{"Very long test string with spaces. Very long test string with spaces."};
    const size_t sizeLimit = 17;
    ASSERT_GT(inputString.size(), sizeLimit);
    const StringList_vt wrappedList = WordWrap(inputString, sizeLimit);

    std::string concatenatedSegments = std::accumulate(wrappedList.begin(), wrappedList.end(), std::string{});
    EXPECT_EQ(concatenatedSegments, inputString);
}
