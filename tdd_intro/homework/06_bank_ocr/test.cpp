#include <gtest/gtest.h>

using OCRData = std::vector<std::string>;

template <class Type>
bool IsSizeInvalid(const Type& data)
{
    return data.size() < 3;
}

std::string OCR2StringDigits(const OCRData& input)
{
    if (IsSizeInvalid(input))
    {
        return "";
    }
    for (size_t i = 0; i < input.size(); ++i)
    {
        if (IsSizeInvalid(input[i]))
        {
            return "";
        }
    }
    const std::string& line1 = input[0];
    const std::string& line2 = input[1];
    const std::string& line3 = input[2];
    if (line1 == "   " &&
        line2 == "  |" &&
        line3 == "  |")
    {
        return "1";
    }
    return "2";
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

TEST(OCR2StringDigits, OCR2StringDigits_Take_One_OCR_Return_2)
{
    OCRData data = {{" _ "},
                    {" _|"},
                    {"|_ "}};
    EXPECT_EQ("2", OCR2StringDigits(OCRData(data)));
}
