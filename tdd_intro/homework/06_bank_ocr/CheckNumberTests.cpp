#include <gtest/gtest.h>
#include "BankOcr.h"

TEST(BankOcr, CheckNumber_checks_valid_number1)
{
    EXPECT_TRUE(BankOcr::detail::CheckNumber(711111111));
}

TEST(BankOcr, CheckNumber_checks_valid_number2)
{
    EXPECT_TRUE(BankOcr::detail::CheckNumber(490867715));
}

TEST(BankOcr, CheckNumber_checks_invalid_number1)
{
    EXPECT_FALSE(BankOcr::detail::CheckNumber(490067715));
}

TEST(BankOcr, CheckNumber_checks_invalid_number2)
{
    EXPECT_FALSE(BankOcr::detail::CheckNumber( 12345678));
}
