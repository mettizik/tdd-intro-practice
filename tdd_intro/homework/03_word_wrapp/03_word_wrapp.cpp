#include <gtest/gtest.h>
#include <gmock/gmock.h>

using StringList_vt = std::vector<std::string>;

StringList_vt WordWrap(const std::string& input, size_t sizeLimit)
{
    StringList_vt result;
    size_t size = input.size();
    size_t offset = 0;
    while (size > 0)
    {
        const size_t segmentSize = std::min(size, sizeLimit);
        result.push_back(input.substr(offset, segmentSize));
        offset += segmentSize;
        size -= segmentSize;
    }
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

    const size_t lastSegmentSize = inputString.size() % sizeLimit;
    const size_t segmentCount = inputString.size() / sizeLimit + (lastSegmentSize > 0 ? 1 : 0);
    for (size_t i = 0; i < segmentCount - 1; ++i)
    {
        EXPECT_EQ(wrappedList[i].size(), sizeLimit);
    }
    EXPECT_EQ(wrappedList[segmentCount - 1].size(), lastSegmentSize);
}
