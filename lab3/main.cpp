#include <iostream>
#include "include/Square.h"
#include "include/Rectangle.h"
#include "include/Trapezoid.h"
#include "include/ShapeArray.h"

int main() {
    ShapeArray shapeArray;

    std::cout << "Input Square:" << std::endl;
    Square* square = new Square;
    std::cin >> *square;
    shapeArray.addShape(square);
    std::cout << *square;
    square->get_center();
    std::cout << "Square area: " << (double)(*square) << std::endl;

    std::cout << "Input Rectangle:" << std::endl;
    Rectangle* rectangle = new Rectangle;
    std::cin >> *rectangle;
    shapeArray.addShape(rectangle);
    std::cout << *rectangle;
    rectangle->get_center();
    std::cout << "Rectangle area: " << (double)(*rectangle) << std::endl;

    std::cout << "Input Trapezoid:" << std::endl;
    Trapezoid* trapezoid = new Trapezoid;
    std::cin >> *trapezoid;
    shapeArray.addShape(trapezoid);
    std::cout << *trapezoid;
    trapezoid->get_center();
    std::cout << "Trapezoid area: " << (double)(*trapezoid) << std::endl;

    std::cout << "\nAll Shapes:\n";
    shapeArray.printShapes();
    std::cout << "Total area of all shapes: " << shapeArray.totalArea() << std::endl;

     std::cout << "Removing shape at index 1." << std::endl;
    shapeArray.removeShape(2);

    std::cout << "\nRemaining Shapes:\n";
    shapeArray.printShapes();
    std::cout << "Total area of remaining shapes: " << shapeArray.totalArea() << std::endl;

    return 0;
}