#include "../include/Trapezoid.h"
#include <iostream>
#include <cmath>

Trapezoid::Trapezoid() : Figure() {}

Trapezoid::Trapezoid(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    _x1 = x1; _y1 = y1;
    _x2 = x2; _y2 = y2;
    _x3 = x3; _y3 = y3;
    _x4 = x4; _y4 = y4;
}

Trapezoid::Trapezoid(const Trapezoid& other) : Figure(other) {}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept : Figure(std::move(other)) {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    Figure::operator=(other);
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        _x1 = other._x1; _y1 = other._y1;
        _x2 = other._x2; _y2 = other._y2;
        _x3 = other._x3; _y3 = other._y3;
        _x4 = other._x4; _y4 = other._y4;

        Figure::operator=(std::move(other));

        other._x1 = other._y1 = other._x2 = other._y2 = 
        other._x3 = other._y3 = other._x4 = other._y4 = 0.0;
    }
    return *this;
}

double Trapezoid::square() const {
    double base1 = std::sqrt(std::pow(_x2 - _x1, 2) + std::pow(_y2 - _y1, 2));
    double base2 = std::sqrt(std::pow(_x4 - _x3, 2) + std::pow(_y4 - _y3, 2));

    double height = std::abs((_x2 - _x1) * (_y1 - _y3) - (_x1 - _x3) * (_y2 - _y1)) /
                    std::sqrt(std::pow(_x2 - _x1, 2) + std::pow(_y2 - _y1, 2));

    return ((base1 + base2) / 2.0) * height;
}

Trapezoid::operator double() const {
    return square();
}

void Trapezoid::get_center() const {
    double center_x = (_x1 + _x2 + _x3 + _x4) / 4.0;
    double center_y = (_y1 + _y2 + _y3 + _y4) / 4.0;
    std::cout << "Trapezoid center: (" << center_x << ", " << center_y << ")" << std::endl;
}

bool Trapezoid::operator==(const Trapezoid& other) const {
    return this->square() == other.square();
}

std::istream& operator>>(std::istream& in, Trapezoid& trap) {
    std::cout << "Enter the coordinates of four vertices (x1, y1), (x2, y2), (x3, y3), (x4, y4): ";
    in >> trap._x1 >> trap._y1 >> trap._x2 >> trap._y2 >> trap._x3 >> trap._y3 >> trap._x4 >> trap._y4;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Trapezoid& trap) {
    out << "Trapezoid:" << std::endl
        << "Vertices: (" << trap._x1 << ", " << trap._y1 << "), ("
        << trap._x2 << ", " << trap._y2 << "), ("
        << trap._x3 << ", " << trap._y3 << "), ("
        << trap._x4 << ", " << trap._y4 << ")" << std::endl;
    return out;
}