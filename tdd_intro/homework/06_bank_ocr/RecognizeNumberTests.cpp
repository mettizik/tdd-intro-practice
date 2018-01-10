#include <gtest/gtest.h>
#include "BankOcr.h"

TEST(BankOcr, RecognizeNumber_recognizes_number123456789)
{
    EXPECT_EQ(123456789, BankOcr::detail::RecognizeNumber("    _  _     _  _  _  _  _ ",
                                                          "  | _| _||_||_ |_   ||_||_|",
                                                          "  ||_  _|  | _||_|  ||_| _|"));
}
