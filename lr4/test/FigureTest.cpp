#include <gtest/gtest.h>
#include "../include/Square.h"
#include "../include/Rectangle.h"
#include "../include/Trapezoid.h"
#include "../include/Array.h"

TEST(PointTest, InitializationAndOutput) {
    Point<int> p(3, 4);
    std::stringstream ss;
    ss << p;

    EXPECT_TRUE(p.x == 3 && p.y == 4 && ss.str() == "(3, 4)");
}

TEST(SquareTest, AreaAndCenterCalculation) {
    Point<int> bottom_left(0, 0);
    Square<int> square(bottom_left, 4);
    Point<int> center = square.center();
    double area = static_cast<double>(square);

    EXPECT_TRUE(area == 16.0 && center.x == 2 && center.y == 2);
}

TEST(SquareTest, VertexOutput) {
    Point<int> bottom_left(0, 0);
    Square<int> square(bottom_left, 4);
    std::stringstream ss;
    ss << square;
    std::string expected_output = "Vertex 1: (0, 0)\nVertex 2: (4, 0)\nVertex 3: (4, 4)\nVertex 4: (0, 4)\n";

    EXPECT_EQ(ss.str(), expected_output);
}

TEST(RectangleTest, AreaAndCenterCalculation) {
    Point<int> rect_bottom_left(0, 0);
    Rectangle<int> rectangle(rect_bottom_left, 3, 5);

    Point<int> center = rectangle.center();
    double area = static_cast<double>(rectangle);

    EXPECT_TRUE(area == 15.0 && center.x == 1 && center.y == 2);
}

TEST(RectangleTest, VertexOutput) {
    Point<int> bottom_left(0, 0);
    Rectangle<int> rectangle(bottom_left, 3, 5);
    std::stringstream ss;
    ss << rectangle;
    std::string expected_output = "Vertex 1: (0, 0)\nVertex 2: (3, 0)\nVertex 3: (3, 5)\nVertex 4: (0, 5)\n";

    EXPECT_EQ(ss.str(), expected_output);
}

TEST(TrapezoidTest, AreaAndCenterCalculation) {
    Point<int> v1(0, 0), v2(4, 0), v3(3, 3), v4(1, 3);
    Trapezoid<int> trapezoid(v1, v2, v3, v4);

    Point<int> center = trapezoid.center();
    int area = static_cast<int>(trapezoid);

    EXPECT_TRUE(area == 9 && center.x == 2 && center.y == 1);
}

TEST(TrapezoidTest, VertexOutput) {
    Point<int> v1(0, 0), v2(4, 0), v3(3, 3), v4(1, 3);
    Trapezoid<int> trapezoid(v1, v2, v3, v4);
    std::stringstream ss;
    ss << trapezoid;
    std::string expected_output = "Vertex 1: (0, 0)\nVertex 2: (4, 0)\nVertex 3: (3, 3)\nVertex 4: (1, 3)\n";

    EXPECT_EQ(ss.str(), expected_output);
}

// Тест увеличения вместимости массива
TEST(ArrayTest, ReserveIncreasesCapacity) {
    Array<Figure<int>> figures;
    size_t initial_capacity = 5;
    figures.reserve(initial_capacity);
    
    figures.push_back(std::make_shared<Square<int>>(Point<int>(0, 0), 2));
    figures.push_back(std::make_shared<Rectangle<int>>(Point<int>(0, 0), 3, 4));
    EXPECT_TRUE(figures.get_size() == 2);

    // Убедимся, что массив работает с увеличенной вместимостью
    for (int i = 2; i < initial_capacity; ++i) {
        figures.push_back(std::make_shared<Square<int>>(Point<int>(i, i), 1));
    }
    EXPECT_TRUE(figures.get_size() == initial_capacity);
}

// Тест уменьшения размера массива до фактического количества элементов
TEST(ArrayTest, ShrinkToFitReducesCapacity) {
    Array<Figure<int>> figures;
    figures.push_back(std::make_shared<Square<int>>(Point<int>(0, 0), 5));
    figures.push_back(std::make_shared<Rectangle<int>>(Point<int>(0, 0), 2, 3));

    figures.reserve(10);  // Увеличим вместимость, чтобы проверить уменьшение
    EXPECT_TRUE(figures.get_size() == 2);  // Размер массива все еще 2

    figures.shrink_to_fit();
    EXPECT_TRUE(figures.get_size() == 2);
}

// Тест на пустые ячейки после удаления элемента
TEST(ArrayTest, RemoveElementLeavesNullptr) {
    Array<Figure<int>> figures;
    figures.push_back(std::make_shared<Square<int>>(Point<int>(0, 0), 4));
    figures.push_back(std::make_shared<Rectangle<int>>(Point<int>(0, 0), 3, 5));

    figures.remove(0);  // Удалим первый элемент
    EXPECT_TRUE(figures.get_size() == 1);

    // Проверяем, что обращение к пустой ячейке не вызывает ошибку
    EXPECT_NO_THROW(figures[0]);

    double remaining_area = static_cast<double>(*figures[0]);
    EXPECT_EQ(remaining_area, 15.0);
}

// Тест для проверки суммарной площади
TEST(ArrayTest, TotalAreaCalculation) {
    Array<Figure<int>> figures;
    figures.push_back(std::make_shared<Square<int>>(Point<int>(0, 0), 4));  // Площадь = 16
    figures.push_back(std::make_shared<Rectangle<int>>(Point<int>(0, 0), 3, 5));  // Площадь = 15

    double total_area = figures.total_area();
    EXPECT_EQ(total_area, 31.0);

    figures.remove(0);  // Удалим квадрат
    total_area = figures.total_area();
    EXPECT_EQ(total_area, 15.0);  // Осталась только площадь прямоугольника
}

TEST(ArrayTest, PushBackAccessAndArea) {
    Array<Figure<int>> figures;
    figures.push_back(std::make_shared<Square<int>>(Point<int>(0, 0), 4));
    figures.push_back(std::make_shared<Rectangle<int>>(Point<int>(0, 0), 3, 5));

    double total_area = static_cast<double>(*figures[0]) + static_cast<double>(*figures[1]);

    EXPECT_TRUE(figures.get_size() == 2 && total_area == 31.0);
}

TEST(ArrayTest, RemoveElementAndAccess) {
    Array<Figure<int>> figures;
    figures.push_back(std::make_shared<Square<int>>(Point<int>(0, 0), 4));
    figures.push_back(std::make_shared<Rectangle<int>>(Point<int>(0, 0), 3, 5));

    figures.remove(0);
    double remaining_area = static_cast<double>(*figures[0]);

    EXPECT_TRUE(figures.get_size() == 1 && remaining_area == 15.0);
}
