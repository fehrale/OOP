#include <gtest/gtest.h>
#include "../include/scaryNum.h"

TEST(ScaryNumTest, ReturnsTrueForMondayWith12)
{
    std::string day = "Monday";
    int num = 12;
    ASSERT_TRUE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsTrueForTuesdayWithNumberGreaterThan95)
{
    std::string day = "Tuesday";
    int num = 96;
    ASSERT_TRUE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsTrueForWednesdayWith34)
{
    std::string day = "Wednesday";
    int num = 34;
    ASSERT_TRUE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsTrueForThursdayWith0)
{
    std::string day = "Thursday";
    int num = 0;
    ASSERT_TRUE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsTrueForFridayWithEvenNumber)
{
    std::string day = "Friday";
    int num = 10;
    ASSERT_TRUE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsTrueForSaturdayWith56)
{
    std::string day = "Saturday";
    int num = 56;
    ASSERT_TRUE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsTrueForSundayWith666)
{
    std::string day = "Sunday";
    int num = 666;
    ASSERT_TRUE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsTrueForSundayWithNegative666)
{
    std::string day = "Sunday";
    int num = -666;
    ASSERT_TRUE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsFalseForMondayWithWrongNumber)
{
    std::string day = "Monday";
    int num = 10;
    ASSERT_FALSE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsFalseForTuesdayWithNumberLessOrEqualTo95)
{
    std::string day = "Tuesday";
    int num = 95;
    ASSERT_FALSE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsFalseForWednesdayWithWrongNumber)
{
    std::string day = "Wednesday";
    int num = 35;
    ASSERT_FALSE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsFalseForThursdayWithWrongNumber)
{
    std::string day = "Thursday";
    int num = 1;
    ASSERT_FALSE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsFalseForFridayWithOddNumber)
{
    std::string day = "Friday";
    int num = 9;
    ASSERT_FALSE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsFalseForSaturdayWithWrongNumber)
{
    std::string day = "Saturday";
    int num = 55;
    ASSERT_FALSE(scaryNum(day, num));
}

TEST(ScaryNumTest, ReturnsFalseForSundayWithWrongNumber)
{
    std::string day = "Sunday";
    int num = 500;
    ASSERT_FALSE(scaryNum(day, num));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
