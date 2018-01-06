#include <gtest/gtest.h>

using OCRData = std::vector<std::string>;


std::string OCR2StringDigits(const OCRData& input)
{
    if (input.empty())
    {
        return "";
    }
    if (input.size() < 3)
    {
        return "";
    }
    return "1";
}

TEST(OCR2StringDigits, OCR2StringDigits_Check_Empty)
{
    EXPECT_EQ("", OCR2StringDigits(OCRData()));
}

TEST(OCR2StringDigits, OCR2StringDigits_Take_One_OCR_Return_1)
{
    OCRData data = {{"   "},
                    {"  |"},
                    {"  |"}};
    EXPECT_EQ("1", OCR2StringDigits(OCRData(data)));
}


TEST(OCR2StringDigits, OCR2StringDigits_Take_Invalid_Size)
{
    OCRData data = {{" _"},
                    {" _|"}};
    EXPECT_EQ("", OCR2StringDigits(OCRData(data)));
}
