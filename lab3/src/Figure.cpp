#include "../include/Figure.h"

Figure::Figure() : _x1(0.0), _y1(0.0), _x2(0.0), _y2(0.0), _x3(0.0), _y3(0.0), _x4(0.0), _y4(0.0) {}

Figure::Figure(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    _x1 = x1; _y1 = y1;
    _x2 = x2; _y2 = y2;
    _x3 = x3; _y3 = y3;
    _x4 = x4; _y4 = y4;
}

Figure::Figure(const Figure& other) {
    _x1 = other._x1; _y1 = other._y1;
    _x2 = other._x2; _y2 = other._y2;
    _x3 = other._x3; _y3 = other._y3;
    _x4 = other._x4; _y4 = other._y4;
}

Figure::Figure(Figure&& other) noexcept {
    _x1 = other._x1; _y1 = other._y1;
    _x2 = other._x2; _y2 = other._y2;
    _x3 = other._x3; _y3 = other._y3;
    _x4 = other._x4; _y4 = other._y4;

    other._x1 = other._y1 = other._x2 = other._y2 = 
    other._x3 = other._y3 = other._x4 = other._y4 = 0.0;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        _x1 = other._x1; _y1 = other._y1;
        _x2 = other._x2; _y2 = other._y2;
        _x3 = other._x3; _y3 = other._y3;
        _x4 = other._x4; _y4 = other._y4;
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        _x1 = other._x1; _y1 = other._y1;
        _x2 = other._x2; _y2 = other._y2;
        _x3 = other._x3; _y3 = other._y3;
        _x4 = other._x4; _y4 = other._y4;

        other._x1 = other._y1 = other._x2 = other._y2 = 
        other._x3 = other._y3 = other._x4 = other._y4 = 0.0;
    }
    return *this;
}

bool Figure::operator==(const Figure& other) const {
    return (_x1 == other._x1 && _y1 == other._y1 &&
            _x2 == other._x2 && _y2 == other._y2 &&
            _x3 == other._x3 && _y3 == other._y3 &&
            _x4 == other._x4 && _y4 == other._y4);
}

std::ostream& operator<<(std::ostream& out, const Figure& fig) {
    out << "Figure:" << std::endl 
        << "1st vertex: (" << fig._x1 << ", " << fig._y1 << ")" << std::endl 
        << "2nd vertex: (" << fig._x2 << ", " << fig._y2 << ")" << std::endl
        << "3rd vertex: (" << fig._x3 << ", " << fig._y3 << ")" << std::endl
        << "4th vertex: (" << fig._x4 << ", " << fig._y4 << ")" << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Figure& fig) {
    std::cout << "Input vertices:" << std::endl;
    in >> fig._x1 >> fig._y1 >> fig._x2 >> fig._y2 >> fig._x3 >> fig._y3 >> fig._x4 >> fig._y4;
    return in;
}

Figure::~Figure() {}