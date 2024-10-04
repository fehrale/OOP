#include <gtest/gtest.h>
#include "../include/Hex.h"

// Тест для оператора сложения
TEST(HexTest, Addition) {
    Hex a{"1A"};
    Hex b{"2B"};
    a += b;  // 1A + 2B = 45
    EXPECT_EQ(a, Hex{"45"});
}

TEST(HexTest, AdditionWithCarry) {
    Hex a{"FF"};
    Hex b{"01"};
    a += b;  // FF + 01 = 100
    EXPECT_EQ(a, Hex{"100"});
}

TEST(HexTest, AdditionWithLeadingZeros) {
    Hex a{"0001"};
    Hex b{"0001"};
    a += b;  // 0001 + 0001 = 2
    EXPECT_EQ(a, Hex{"2"});
}

// Тест для оператора вычитания
TEST(HexTest, Subtraction) {
    Hex a{"2B"};
    Hex b{"1A"};
    a -= b;  // 2B - 1A = 11
    EXPECT_EQ(a, Hex{"11"});
}

TEST(HexTest, SubtractionWithBorrow) {
    Hex a{"10"};
    Hex b{"A"};
    a -= b;  // 10 - A = 6
    EXPECT_EQ(a, Hex{"6"});
}

TEST(HexTest, SubtractionUnderflow) {
    Hex a{"1A"};
    Hex b{"2B"};
    EXPECT_THROW(a -= b, std::invalid_argument);  // Ожидаем исключение при вычитании большего числа
}

// Тесты для конструкторов
TEST(HexTest, ConstructorFromString) {
    Hex a{"1A"};
    EXPECT_EQ(a, Hex{"1A"});
}

TEST(HexTest, ConstructorFromInitializerList) {
    Hex a{std::initializer_list<unsigned char>{'1', 'A'}};
    EXPECT_EQ(a, Hex{"1A"});
}

TEST(HexTest, DefaultConstructor) {
    Hex a;
    EXPECT_EQ(a, Hex{"0"});
}

// Тесты на исключения
TEST(HexTest, InvalidDigitException) {
    EXPECT_THROW(Hex{"1G"}, std::invalid_argument);  // 'G' не является допустимой цифрой
}

TEST(HexTest, OperatorAssignment) {
    Hex a{"1A"};
    Hex b = a;
    EXPECT_EQ(b, a);  // Проверка корректности оператора присваивания
}

TEST(HexTest, MoveConstructor) {
    Hex a{"1A"};
    Hex b = std::move(a);  // Проверка перемещения
    EXPECT_EQ(b, Hex{"1A"});
    EXPECT_EQ(a.getSize(), 0);  // Ожидаем, что перемещённый объект будет пустым
}

// Тест на сравнение
TEST(HexTest, ComparisonOperators) {
    Hex a{"1A"};
    Hex b{"2B"};
    EXPECT_LT(a, b);
    EXPECT_GT(b, a);
    EXPECT_EQ(a, Hex{"1A"});
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
