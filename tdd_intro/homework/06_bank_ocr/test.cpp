#include <gtest/gtest.h>

using OCRData = std::vector<std::string>;

template <class Type>
bool IsSizeInvalid(const Type& data)
{
    return data.size() < 3;
}

std::string OCR2StringDigits(const OCRData& input)
{
    if (input.empty() || IsSizeInvalid(input))
    {
        return "";
    }
    if (IsSizeInvalid(input[0]) || IsSizeInvalid(input[1]) || IsSizeInvalid(input[2]))
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


TEST(OCR2StringDigits, OCR2StringDigits_Take_Invalid_Row_Count)
{
    OCRData data = {{" _"},
                    {" _|"}};
    EXPECT_EQ("", OCR2StringDigits(OCRData(data)));
}

TEST(OCR2StringDigits, OCR2StringDigits_Take_Invalid_Column_Count)
{
    OCRData data = {{" _ "},
                    {"|_|"},
                    {" _"}};
    EXPECT_EQ("", OCR2StringDigits(OCRData(data)));
}
