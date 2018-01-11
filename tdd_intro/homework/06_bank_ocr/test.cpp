#include <gtest/gtest.h>

//LIST
//1. Single symbol parsing
//2. 3 symbols parsing
//3. 9 symbols parsing
//4. work with file

namespace
{
    using Lines = std::vector<std::string>;
    using Symbol = std::vector<Lines>;

    const std::string white          = "   ";
    const std::string lastPipe       = "  |";
    const std::string midUnder       = " _ ";
    const std::string whiteUnderPipe = " _|";
    const std::string pipeUnderWhite = "|_ ";
    const std::string pipeUnderPipe  = "|_|";
    const std::string pipeWhitePipe  = "| |";
}

int Parse(const Lines& lines)
{
    if (lines.size() == 3
        && lines[0].size() == 3
        && lines[1].size() == 3
        && lines[2].size() == 3)
    {
        if (lines[0] == midUnder)
        {
            if (lines[1] == whiteUnderPipe)
            {
                if (lines[2] == pipeUnderWhite)
                {
                    return 2;
                }
                else if (lines[2] == whiteUnderPipe)
                {
                    return 3;
                }
            }
            else if (lines[1] == pipeUnderWhite)
            {
                if (lines[2] == whiteUnderPipe)
                {
                    return 5;
                }
                else if (lines[2] == pipeUnderPipe)
                {
                    return 6;
                }
            }
            else if (lines[1] == pipeUnderPipe)
            {
                if (lines[2] == pipeUnderPipe)
                {
                    return 8;
                }
                else if (lines[2] == whiteUnderPipe)
                {
                    return 9;
                }
            }
            else if (lines[1] == lastPipe
                     && lines[2] == lastPipe)
            {
                return 7;
            }
            else if (lines[1] == pipeWhitePipe
                     && lines[2] == pipeUnderPipe)
            {
                return 0;
            }
        }
        else if (lines[0] == white
                 && lines[1] == pipeUnderPipe
                 && lines[2] == lastPipe)
        {
            return 4;
        }
        return 1;
    }
    return -1;
}

Symbol Decompose(const Lines& lines)
{
    if (lines.size() == 3
        && lines[0].size() == 3
        && lines[1].size() == 3
        && lines[2].size() == 3)
    {
        Symbol s(1);
        return s;
    }

    if (lines.size() == 3
        && lines[0].size() == 6
        && lines[1].size() == 6
        && lines[2].size() == 6)
    {
        Symbol s(2);
        return s;
    }
    return Symbol();
}

TEST(Bank, EmptyStrings)
{
    Lines lines;
    EXPECT_EQ(Parse(lines), -1);
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

TEST(Bank, Single_eight)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(pipeUnderPipe);
    lines.push_back(pipeUnderPipe);

    EXPECT_EQ(Parse(lines), 8);
}

TEST(Bank, Single_nine)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(pipeUnderPipe);
    lines.push_back(whiteUnderPipe);

    EXPECT_EQ(Parse(lines), 9);
}

TEST(Bank, Single_zero)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(pipeWhitePipe);
    lines.push_back(pipeUnderPipe);

    EXPECT_EQ(Parse(lines), 0);
}

TEST(Bank, InvalidStrings)
{
    Lines lines;
    lines.push_back(midUnder + "_");
    lines.push_back(pipeWhitePipe);
    lines.push_back(pipeUnderPipe);

    EXPECT_EQ(Parse(lines), -1);
}

TEST(Bank, InvalidStrings1)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(pipeWhitePipe);

    EXPECT_EQ(Parse(lines), -1);
}

TEST(Bank, StringDecomposing)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(midUnder);
    lines.push_back(midUnder);

    EXPECT_EQ(Decompose(lines).size(), 1);
}

TEST(Bank, StringDecomposingInvalidData)
{
    Lines lines;
    lines.push_back(midUnder);
    lines.push_back(midUnder);

    EXPECT_EQ(Decompose(lines).size(), 0);
}

TEST(Bank, StringDecomposingInvalidData1)
{
    Lines lines;
    lines.push_back(midUnder + " ");
    lines.push_back(midUnder);
    lines.push_back(midUnder);

    EXPECT_EQ(Decompose(lines).size(), 0);
}

TEST(Bank, StringDecomposing2Elements)
{
    Lines lines;
    lines.push_back(midUnder + midUnder);
    lines.push_back(midUnder + midUnder);
    lines.push_back(midUnder + midUnder);

    EXPECT_EQ(Decompose(lines).size(), 2);
}
