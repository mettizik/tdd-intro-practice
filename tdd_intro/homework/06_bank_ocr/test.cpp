#include <gtest/gtest.h>

using OCRData = std::vector<std::string>;

template <class Type>
bool IsSizeInvalid(const Type& data)
{
    return data.size() < 3;
}

std::string OneOCR2StringDigit(const std::string& line1,
                               const std::string& line2,
                               const std::string& line3)
{
    using OCRDataTemplate = std::vector<std::vector<std::string>>;
    OCRDataTemplate templateData = {
                                    {
                                        {"   "},
                                        {"  |"},
                                        {"  |"}
                                    },
                                    {
                                        {" _ "},
                                        {" _|"},
                                        {"|_ "}
                                    },
                                    {
                                        {" _ "},
                                        {" _|"},
                                        {" _|"}
                                    },
                                    {
                                        {"   "},
                                        {"|_|"},
                                        {"  |"}
                                    },
                                    {
                                        {" _ "},
                                        {"|_ "},
                                        {" _|"}
                                    },
                                    {
                                        {" _ "},
                                        {"|_ "},
                                        {"|_|"}
                                    },
                                    {
                                        {" _ "},
                                        {"  |"},
                                        {"  |"}
                                    },
                                    {
                                        {" _ "},
                                        {"|_|"},
                                        {"|_|"}
                                    },
                                    {
                                        {" _ "},
                                        {"|_|"},
                                        {" _|"}
                                    }
                                    };

    for (size_t i = 0; i < templateData.size(); ++i)
    {
        if (line1 == templateData[i][0] &&
            line2 == templateData[i][1] &&
            line3 == templateData[i][2])
        {
            return std::to_string(i + 1);
        }
    }
    return "";
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
    return OneOCR2StringDigit(input[0], input[1], input[2]);
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


TEST(OCR2StringDigits, OCR2StringDigits_Take_One_OCR_Return_3)
{
    OCRData data = {{" _ "},
                    {" _|"},
                    {" _|"}};
    EXPECT_EQ("3", OCR2StringDigits(OCRData(data)));
}
