#include <gtest/gtest.h>

bool polindrome(int number)
{
 int i=1; int j=0;
 while(i < number) {i = i * 10; j++;}
 i = i / 10;
 for (int l = 0; l < j / 2; l++)
 {
     if (number / i != number % 10) return false;
     else
     {
         number = (number / i) * i;
         number = (number - number % 10) / 10;
     }
 }
 return true;
}

TEST(pol, acc)
{
    EXPECT_TRUE(polindrome(12344321));
    EXPECT_TRUE(polindrome(1234321));
    EXPECT_FALSE(polindrome(2334));
}
