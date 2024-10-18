#pragma once

#include "Figure.h"

class Square : public Figure {
public:
    Square();
    Square(double x1, double y1, double side_length);
    Square(const Square& other);
    Square(Square&& other) noexcept;

    Square& operator=(const Square& other);
    Square& operator=(Square&& other) noexcept;

    double square() const override;
    operator double() const override; 
    void get_center() const override;

    bool operator==(const Square& other) const;

    friend std::istream& operator>>(std::istream& in, Square& sq);
    friend std::ostream& operator<<(std::ostream& out, const Square& sq);
};