/*
Convert a trinary number, represented as a string (e.g. '102012'), to its decimal equivalent using first principles.

The program should consider strings specifying an invalid trinary as the value 0.

Trinary numbers contain three symbols: 0, 1, and 2.

The last place in a trinary number is the 1's place. The second to last is the 3's place, the third to last is the 9's place, etc.

# "102012"
    1       0       2       0       1       2    # the number
1*3^5   + 0*3^4 + 2*3^3 + 0*3^2 + 1*3^1 + 2*3^0    # the value
  243   +   0 +    54 +     0 +     3 +     2 =  302

If your language provides a method in the standard library to perform the conversion, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>
#include <string>
#include <exception>
#include <cmath>

size_t validate_digit(char val, size_t base)
{
  const auto res = val - 0x30;
  if (!(res >= 0 && res < base))
  {
    throw std::runtime_error("Invalid digit for provided base!");
  }
  return res;
}

size_t parse_digit_line_base(const std::string &digitsLine, size_t base)
{
  assert(base > 0 && base <= 10);
  size_t result = 0;
  auto power = digitsLine.size() - 1;
  for (auto digit : digitsLine)
  {
    result += validate_digit(digit, base) * std::pow(base, power--);
  }
  return result;
}

size_t trinary(const std::string &line)
{
  try
  {
    return parse_digit_line_base(line, 3);
  }
  catch (const std::exception &ex)
  {
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////

TEST(trinary, trinary_returns_zero_if_receives_empty_string)
{
  EXPECT_EQ(0, trinary(""));
}

TEST(trinary, trinary_returns_zero_if_receives_zero)
{
  EXPECT_EQ(0, trinary("0"));
}

TEST(trinary, trinary_returns_one_if_receives_one)
{
  EXPECT_EQ(1, trinary("1"));
}

TEST(trinary, trinary_returns_zero_if_receives_invalid_symbol)
{
  EXPECT_EQ(0, trinary("a"));
  EXPECT_EQ(0, trinary("ab"));
  EXPECT_EQ(0, trinary("x;"));
}

TEST(trinary, trinary_returns_zero_if_receives_negative_number)
{
  EXPECT_EQ(0, trinary("-1"));
}

TEST(trinary, trinary_returns_zero_if_receives_number_more_than_2)
{
  EXPECT_EQ(0, trinary("3"));
}

TEST(trinary, trinary_returns_three_if_receives_10)
{
  EXPECT_EQ(3, trinary("10"));
}

TEST(trinary, trinary_returns_four_if_receives_11)
{
  EXPECT_EQ(4, trinary("11"));
}

TEST(trinary, trinary_returns_37_if_receives_121)
{
  EXPECT_EQ(16, trinary("121"));
}

TEST(trinary, acceptance_test)
{
  EXPECT_EQ(302, trinary("102012"));
}

TEST(decimal, acceptance_test)
{
  EXPECT_EQ(123456787643, parse_digit_line_base("123456787643", 10));
}

TEST(octal, acceptance_test)
{
  EXPECT_EQ(01234567, parse_digit_line_base("1234567", 8));
}
