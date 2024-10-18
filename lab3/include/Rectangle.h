#pragma once

#include "Figure.h"

class Rectangle : public Figure {
public:
    Rectangle();
    Rectangle(double x1, double y1, double width, double height);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    double square() const override;
    operator double() const override; 
    void get_center() const override;


    bool operator==(const Rectangle& other) const;

    friend std::istream& operator>>(std::istream& in, Rectangle& rect);
    friend std::ostream& operator<<(std::ostream& out, const Rectangle& rect);
};
