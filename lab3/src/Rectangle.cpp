#include "../include/Rectangle.h"
#include <iostream>

Rectangle::Rectangle() : Figure() {}

Rectangle::Rectangle(double x1, double y1, double width, double height) {
    _x1 = x1; _y1 = y1;
    _x2 = x1 + width; _y2 = y1;
    _x3 = x1 + width; _y3 = y1 + height;
    _x4 = x1; _y4 = y1 + height;
}

Rectangle::Rectangle(const Rectangle& other) : Figure(other) {}

Rectangle::Rectangle(Rectangle&& other) noexcept : Figure(std::move(other)) {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    Figure::operator=(other);
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

double Rectangle::square() const {
    double width = _x2 - _x1;
    double height = _y4 - _y1;
    return width * height;
}

Rectangle::operator double() const {
    return square(); 
}

void Rectangle::get_center() const {
    double center_x = (_x1 + _x3) / 2;
    double center_y = (_y1 + _y3) / 2;
    std::cout << "Rectangle center: (" << center_x << ", " << center_y << ")" << std::endl;
}

bool Rectangle::operator==(const Rectangle& other) const {
    return this->square() == other.square();
}

std::istream& operator>>(std::istream& in, Rectangle& rect) {
    double width, height;
    std::cout << "Enter the bottom-left vertex (x1, y1), width, and height: ";
    in >> rect._x1 >> rect._y1 >> width >> height;
    rect._x2 = rect._x1 + width; rect._y2 = rect._y1;
    rect._x3 = rect._x1 + width; rect._y3 = rect._y1 + height;
    rect._x4 = rect._x1; rect._y4 = rect._y1 + height;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Rectangle& rect) {
    out << "Rectangle:" << std::endl
        << "Vertices: (" << rect._x1 << ", " << rect._y1 << "), ("
        << rect._x2 << ", " << rect._y2 << "), ("
        << rect._x3 << ", " << rect._y3 << "), ("
        << rect._x4 << ", " << rect._y4 << ")" << std::endl;
    return out;
}