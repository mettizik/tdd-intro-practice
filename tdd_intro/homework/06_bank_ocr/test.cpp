#include <gtest/gtest.h>

using OCRData = std::vector<std::vector<char>>;


std::string OCR2StringDigits(const OCRData& /*input*/)
{
    return "";
}

TEST(OCR2StringDigits, OCR2StringDigits)
{
    EXPECT_EQ("", OCR2StringDigits(OCRData()));
}
