#include "../include/Square.h"
#include <iostream>

Square::Square() : Figure() {}

Square::Square(double x1, double y1, double side_length) {
    _x1 = x1; _y1 = y1;
    _x2 = x1 + side_length; _y2 = y1;
    _x3 = x1 + side_length; _y3 = y1 + side_length;
    _x4 = x1; _y4 = y1 + side_length;
}

Square::Square(const Square& other) : Figure(other) {}

Square::Square(Square&& other) noexcept : Figure(std::move(other)) {}

Square& Square::operator=(const Square& other) {
    Figure::operator=(other);
    return *this;
}

Square& Square::operator=(Square&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}

double Square::square() const {
    double side_length = _x2 - _x1;
    return side_length * side_length;
}

Square::operator double() const {
    return square();
}

void Square::get_center() const {
    double center_x = (_x1 + _x3) / 2;
    double center_y = (_y1 + _y3) / 2;
    std::cout << "Square center: (" << center_x << ", " << center_y << ")" << std::endl;
}

bool Square::operator==(const Square& other) const {
    return this->square() == other.square();
}

std::istream& operator>>(std::istream& in, Square& sq) {
    double side_length;
    std::cout << "Enter the bottom-left vertex (x1, y1) and side length: ";
    in >> sq._x1 >> sq._y1 >> side_length;
    sq._x2 = sq._x1 + side_length; sq._y2 = sq._y1;
    sq._x3 = sq._x1 + side_length; sq._y3 = sq._y1 + side_length;
    sq._x4 = sq._x1; sq._y4 = sq._y1 + side_length;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Square& sq) {
    out << "Square:" << std::endl
        << "Vertices: (" << sq._x1 << ", " << sq._y1 << "), ("
        << sq._x2 << ", " << sq._y2 << "), ("
        << sq._x3 << ", " << sq._y3 << "), ("
        << sq._x4 << ", " << sq._y4 << ")" << std::endl;
    return out;
}