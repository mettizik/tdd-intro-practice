#include <gtest/gtest.h>

/**
 * User Story 1
The following format is created by the machine:

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

/////////////////////////////////////
///
///
  {
      {" _ "},
      {"| |"},
      {"|_|"}
  },
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
///
/////////////////////////////////////

 */

// Tests list
// Parse 1 digit
// Parse several digits
// String has 27 columns and 3 rows

using OCRData = std::vector<std::string>;
using OCRDataVector = std::vector<OCRData>;
namespace
{
    const OCRDataVector s_constsVector = OCRDataVector{
                           {{" _ "},
                            {"| |"},
                            {"|_|"}},
                           {{"   "},
                            {"  |"},
                            {"  |"}}
                                  };
}

std::string OCRToString(const OCRData& ocr)
{
    for (size_t i = 0; i < s_constsVector.size(); ++i)
    {
        if (ocr == s_constsVector[i])
        {
            return std::to_string(i);
        }
    }
    return "2";
}

std::string RecognizeNumber(const OCRData& ocr)
{
    std::string number;

    const size_t digitWidth = 3;
    for (size_t pos = 0; pos < ocr.front().size(); pos += digitWidth)
    {
        number += OCRToString({
                                  ocr[0].substr(pos, digitWidth),
                                  ocr[1].substr(pos, digitWidth),
                                  ocr[2].substr(pos, digitWidth),
                              });
    }

    return number;
}

TEST(OCRToString, OCRToString_Parse_0)
{
    EXPECT_EQ("0", OCRToString({{" _ "},
                                {"| |"},
                                {"|_|"}}));
}

TEST(OCRToString, OCRToString_Parse_1)
{
    EXPECT_EQ("1", OCRToString({{"   "},
                                {"  |"},
                                {"  |"}}));
}

TEST(OCRToString, OCRToString_Parse_2)
{
    EXPECT_EQ("2", OCRToString({{" _ "},
                                {" _|"},
                                {"|_ "}}));
}

TEST(OCRToString, RecognizeNumber_parses_two_digit)
{
    EXPECT_EQ("21", RecognizeNumber({{" _    "},
                                     {" _|  |"},
                                     {"|_   |"}}));
}

TEST(OCRToString, RecognizeNumber_parses_nine_digit)
{
    EXPECT_EQ("123456789", RecognizeNumber({{"    _  _     _  _  _  _  _ "},
                                            {"  | _| _||_||_ |_   ||_||_|"},
                                            {"  ||_  _|  | _||_|  ||_| _|"}}));
}
