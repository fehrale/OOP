#include <iostream>
#include "include/Square.h"
#include "include/Rectangle.h"
#include "include/Trapezoid.h"
#include "include/Array.h"

int main() {
    Array<Figure<int>> figures;

    std::cout << "Input Square:\n";
    Point<int> bottom_left;
    int side_length;
    std::cout << "Enter the bottom-left vertex (x1, y1) and side length: ";
    std::cin >> bottom_left >> side_length;
    figures.push_back(std::make_shared<Square<int>>(bottom_left, side_length));

    std::cout << "\nInput Rectangle:\n";
    Point<int> rect_bottom_left;
    int width, height;
    std::cout << "Enter the bottom-left vertex (x1, y1), width, and height: ";
    std::cin >> rect_bottom_left >> width >> height;
    figures.push_back(std::make_shared<Rectangle<int>>(rect_bottom_left, width, height));

    std::cout << "\nInput Trapezoid:\n";
    Point<int> v1, v2, v3, v4;
    std::cout << "Enter four vertices (x1, y1), (x2, y2), (x3, y3), (x4, y4): ";
    std::cin >> v1 >> v2 >> v3 >> v4;
    figures.push_back(std::make_shared<Trapezoid<int>>(v1, v2, v3, v4));
    
    std::cout << "All Shapes:" << std::endl;
    figures.print_all();

    std::cout << "Total area: " << figures.total_area() << std::endl;

    figures.remove(1);

    std::cout << "Remaining Shapes:" << std::endl;
    figures.print_all();

    std::cout << "Total area of remaining shapes: " << figures.total_area() << std::endl;

    return 0;
}