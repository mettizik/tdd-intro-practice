#include <cassert>
#include "BankOcr.h"

int BankOcr::detail::RecognizeDigit(const std::string& line1, const std::string& line2, const std::string& line3)
{
    if      (line1 == "   " && line2 == "  |" && line3 == "  |")
    {
        return 1;
    }
    else if (line1 == " _ " && line2 == " _|" && line3 == "|_ ")
    {
        return 2;
    }
    else if (line1 == " _ " && line2 == " _|" && line3 == " _|")
    {
        return 3;
    }
    else if (line1 == "   " && line2 == "|_|" && line3 == "  |")
    {
        return 4;
    }
    else if (line1 == " _ " && line2 == "|_ " && line3 == " _|")
    {
        return 5;
    }
    else if (line1 == " _ " && line2 == "|_ " && line3 == "|_|")
    {
        return 6;
    }
    else if (line1 == " _ " && line2 == "  |" && line3 == "  |")
    {
        return 7;
    }
    else if (line1 == " _ " && line2 == "|_|" && line3 == "|_|")
    {
        return 8;
    }
    else if (line1 == " _ " && line2 == "|_|" && line3 == " _|")
    {
        return 9;
    }
    return 0;
}

int BankOcr::detail::RecognizeNumber(const std::string& line1, const std::string& line2, const std::string& line3)
{
    assert(line1.size() == 27 && line2.size() == 27 && line3.size() == 27);

    int result = 0;
    for (size_t i = 0; i < 27; i += 3)
    {
        result *= 10;
        result += RecognizeDigit(line1.substr(i, 3), line2.substr(i, 3), line3.substr(i, 3));
    }
    return result;
}

bool BankOcr::detail::CheckNumber(int number)
{
    assert(number >= 0 && number <= 999999999);

    int remainder = number;
    int result = 0;
    for (int multiplier = 1; multiplier <= 9; ++multiplier)
    {
        const int digit = remainder % 10;
        remainder /= 10;
        result += digit * multiplier;
    }
    return result % 11 == 0;
}
