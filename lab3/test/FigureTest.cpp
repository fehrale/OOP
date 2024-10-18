#include <gtest/gtest.h>
#include "../include/Square.h"
#include "../include/Rectangle.h"
#include "../include/Trapezoid.h"
#include "../include/ShapeArray.h"
#include <sstream>

TEST(SquareTest, AreaCalculation) {
    Square square(0, 0, 4);
    ASSERT_DOUBLE_EQ(square.square(), 16); 
}

TEST(SquareTest, CenterCalculation) {
    Square square(0, 0, 4);
    testing::internal::CaptureStdout();
    square.get_center();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Square center: (2, 2)\n");
}

TEST(SquareTest, CopyAssignment) {
    Square square1(0, 0, 4);
    Square square2 = square1;
    ASSERT_EQ(square1, square2);
}

TEST(SquareTest, MoveAssignment) {
    Square square1(0, 0, 4);
    Square square2 = std::move(square1);
    ASSERT_DOUBLE_EQ(square2.square(), 16);
}

// Тесты для класса Rectangle
TEST(RectangleTest, AreaCalculation) {
    Rectangle rectangle(0, 0, 4, 6);
    ASSERT_DOUBLE_EQ(rectangle.square(), 24);
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle rectangle(0, 0, 4, 6);
    testing::internal::CaptureStdout();
    rectangle.get_center();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Rectangle center: (2, 3)\n");
}

TEST(RectangleTest, CopyAssignment) {
    Rectangle rectangle1(0, 0, 4, 6);
    Rectangle rectangle2 = rectangle1;
    ASSERT_EQ(rectangle1, rectangle2);
}

TEST(RectangleTest, MoveAssignment) {
    Rectangle rectangle1(0, 0, 4, 6);
    Rectangle rectangle2 = std::move(rectangle1);
    ASSERT_DOUBLE_EQ(rectangle2.square(), 24);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid trapezoid(0, 0, 4, 0, 3, 3, 1, 3); 
    EXPECT_DOUBLE_EQ(trapezoid.square(), 9);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid trapezoid(0, 0, 4, 0, 3, 3, 1, 3);
    testing::internal::CaptureStdout();
    trapezoid.get_center();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Trapezoid center: (2, 1.5)\n");
}

TEST(TrapezoidTest, CopyAssignment) {
    Trapezoid trapezoid1(0, 0, 4, 0, 3, 3, 1, 3);
    Trapezoid trapezoid2 = trapezoid1;
    ASSERT_EQ(trapezoid1, trapezoid2);
}

TEST(TrapezoidTest, MoveAssignment) {
    Trapezoid trapezoid1(0, 0, 4, 0, 3, 3, 1, 3);
    Trapezoid trapezoid2 = std::move(trapezoid1);
    ASSERT_DOUBLE_EQ(trapezoid2.square(), 9);
}

TEST(ShapeArrayTest, AddShape) {
    ShapeArray shapeArray;
    Square* square = new Square(0, 0, 4);
    shapeArray.addShape(square);
    ASSERT_DOUBLE_EQ(shapeArray.totalArea(), 16.0);
}

TEST(ShapeArrayTest, RemoveShape) {
    ShapeArray shapeArray;
    Square* square = new Square(0, 0, 4);
    shapeArray.addShape(square);
    shapeArray.removeShape(0);
    ASSERT_DOUBLE_EQ(shapeArray.totalArea(), 0.0);
}

TEST(ShapeArrayTest, TotalArea) {
    ShapeArray shapeArray;
    Square* square = new Square(0, 0, 4);
    Rectangle* rectangle = new Rectangle(0, 0, 4, 6);
    
    shapeArray.addShape(square);
    shapeArray.addShape(rectangle);
    
    ASSERT_DOUBLE_EQ(shapeArray.totalArea(), 16.0 + 24.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
