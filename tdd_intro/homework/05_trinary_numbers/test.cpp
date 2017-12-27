/*
Given a phrase, count the occurrences of each word in that phrase.

For example for the input "olly olly in come free"

olly: 2
in: 1
come: 1
free: 1

*/

#include <gtest/gtest.h>
#include <cmath>

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

//unsigned int GetValue(const std::string&)
//{
//    return 0;
//}

//unsigned int GetValue(const std::string& str)
//{
//    char ch = str[str.length() - 1];
//    if (ch == '1')
//    {
//        return 1;
//    }
//    return 0;
//}

//unsigned int GetValue(const std::string& str)
//{
//    unsigned int res = 0;
//    char ch = str[str.length() - 1];
//    if (ch == '1')
//    {
//        res = 1;
//    }
//    return res;
//}

//unsigned int GetValue(const std::string& str)
//{
//    unsigned int res = 0;
//    char ch = str[str.length() - 1];
//    if (ch == '1')
//    {
//        res = 1;
//    }
//    if (ch == '2')
//    {
//        res = 2;
//    }
//    return res;
//}

//unsigned int GetValue(const std::string& str)
//{
//    unsigned int res = 0;
//    char ch = str[str.length() - 1];
//    if (ch == '1')
//    {
//        res = 1;
//    }
//    if (ch == '2')
//    {
//        res = 2;
//    }
//    if (ch == '3')
//    {
//        res = 3;
//    }
//    return res;
//}

//unsigned int GetValue(const std::string& str)
//{
//    unsigned int res = 0;
//    if (str.length() == 1)
//    {
//        char ch = str[str.length() - 1];
//        if (ch == '1')
//        {
//            res = 1;
//        }
//        if (ch == '2')
//        {
//            res = 2;
//        }
//        if (ch == '3')
//        {
//            res = 3;
//        }
//    }
//    return res;
//}

//unsigned int GetValue(const std::string& str)
//{
//    unsigned int res = 0;
//    if (str.length() > 0)
//    {
//        char ch = str[str.length() - 1];
//        if (ch == '1')
//        {
//            res = 1;
//        }
//        if (ch == '2')
//        {
//            res = 2;
//        }
//        if (ch == '3')
//        {
//            res = 3;
//        }
//    }
//    if (str.length() > 1)
//    {
//        char ch = str[str.length() - 2];
//        if (ch == '1')
//        {
//            res += 3 * 1;
//        }
//        if (ch == '2')
//        {
//            res += 3 * 2;
//        }
//        if (ch == '3')
//        {
//            res += 3 * 3;
//        }
//    }
//    return res;
//}

//unsigned int GetValue(const std::string& str)
//{
//    unsigned int res = 0;
//    for (unsigned int i = 0; str.length() > i; i++)
//    {
//        char ch = str[str.length() - i - 1];
//        if (ch == '1')
//        {
//            res += 1 * static_cast<unsigned int>(pow(3, i));
//        }
//        if (ch == '2')
//        {
//            res += 2 * static_cast<unsigned int>(pow(3, i));
//        }
//        if (ch == '3')
//        {
//            res += 3 * static_cast<unsigned int>(pow(3, i));
//        }
//    }
//    return res;
//}

//unsigned int GetValue(const std::string& str)
//{
//    unsigned int res = 0;
//    for (unsigned int i = 0; str.length() > i; i++)
//    {
//        char ch = str[str.length() - i - 1];
//        if (ch == '1')
//        {
//            res += 1 * static_cast<unsigned int>(pow(3, i));
//        }
//        if (ch == '2')
//        {
//            res += 2 * static_cast<unsigned int>(pow(3, i));
//        }
//    }
//    return res;
//}

unsigned int GetValue(const std::string& str)
{
    unsigned int res = 0;
    for (unsigned int i = 0; str.length() > i; i++)
    {
        char ch = str[str.length() - i - 1] - '0';
        if (ch == 1 || ch == 2)
        {
            res += ch * static_cast<unsigned int>(pow(3, i));
        }
    }
    return res;
}

TEST (Numbers, InvalidValue)
{
    ASSERT_EQ(0, GetValue("4"));
}

TEST (Numbers, one_digit_1)
{
    ASSERT_EQ(1, GetValue("1"));
}

TEST (Numbers, one_digit_2)
{
    ASSERT_EQ(2, GetValue("2"));
}

//TEST (Numbers, one_digit_3) //incorrect test
//{
//    ASSERT_EQ(3, GetValue("3"));
//}

TEST (Numbers, EmptyStr)
{
    ASSERT_EQ(0, GetValue(""));
}

TEST (Numbers, two_digit_1)
{
    ASSERT_EQ(5, GetValue("12"));
}

TEST (Numbers, Acceptance)
{
    ASSERT_EQ(302, GetValue("102012"));
}

TEST (Numbers, InvalidValue_1)
{
    ASSERT_EQ(0, GetValue("3"));
}


