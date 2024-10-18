#pragma once

#include "Figure.h"

class Trapezoid : public Figure {
public:
    Trapezoid();
    Trapezoid(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    double square() const override;
    operator double() const override;
    void get_center() const override;

    bool operator==(const Trapezoid& other) const;

    friend std::istream& operator>>(std::istream& in, Trapezoid& trap);
    friend std::ostream& operator<<(std::ostream& out, const Trapezoid& trap);
};
