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
