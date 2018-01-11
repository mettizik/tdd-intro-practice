#include <gtest/gtest.h>

//LIST
//1. Single symbol parsing
//2. 3 symbols parsing
//3. 9 symbols parsing
//4. work with file

namespace
{
    using Lines = std::vector<std::string>;

    const std::string white          = "   ";
    const std::string lastPipe       = "  |";
    const std::string midUnder       = " _ ";
    const std::string whiteUnderPipe = " _|";
    const std::string pipeUnderWhite = "|_ ";
    const std::string pipeUnderPipe  = "|_|";
}

int Parse(const Lines& lines)
{
    if (!lines.empty())
    {
        if (lines[0] == midUnder
            && lines[1] == whiteUnderPipe
            && lines[2] == pipeUnderWhite)
        {
            return 2;
        }
        else if (lines[0] == midUnder
                 && lines[1] == whiteUnderPipe
                 && lines[2] == whiteUnderPipe)
        {
            return 3;
        }
        else if (lines[0] == white
                 && lines[1] == pipeUnderPipe
                 && lines[2] == lastPipe)
        {
            return 4;
        }
        else if (lines[0] == midUnder
                 && lines[1] == pipeUnderWhite
                 && lines[2] == whiteUnderPipe)
        {
            return 5;
        }
        else if (lines[0] == midUnder
                 && lines[1] == pipeUnderWhite
                 && lines[2] == pipeUnderPipe)
        {
            return 6;
        }
        else if (lines[0] == midUnder
                 && lines[1] == lastPipe
                 && lines[2] == lastPipe)
        {
            return 7;
        }

        return 1;
    }
    return 0;
}

TEST(Bank, EmptyStrings)
{
    Lines lines;
    EXPECT_EQ(Parse(lines), 0);
}

TEST(Bank, Single_one)
{
    Lines lines;
    lines.push_back(white);
    lines.push_back(lastPipe);
    lines.push_back(lastPipe);

    EXPECT_EQ(Parse(lines), 1);
}

TEST(Bank, Single_two)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(whiteUnderPipe);
    lines.push_back(pipeUnderWhite);

    EXPECT_EQ(Parse(lines), 2);
}

TEST(Bank, Single_three)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(whiteUnderPipe);
    lines.push_back(whiteUnderPipe);

    EXPECT_EQ(Parse(lines), 3);
}

TEST(Bank, Single_four)
{
    Lines lines;
    lines.push_back(white);
    lines.push_back(pipeUnderPipe);
    lines.push_back(lastPipe);

    EXPECT_EQ(Parse(lines), 4);
}

TEST(Bank, Single_five)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(pipeUnderWhite);
    lines.push_back(whiteUnderPipe);

    EXPECT_EQ(Parse(lines), 5);
}

TEST(Bank, Single_six)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(pipeUnderWhite);
    lines.push_back(pipeUnderPipe);

    EXPECT_EQ(Parse(lines), 6);
}

TEST(Bank, Single_seven)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(lastPipe);
    lines.push_back(lastPipe);

    EXPECT_EQ(Parse(lines), 7);
}
