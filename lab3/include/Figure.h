#pragma once

#include <iostream>

class Figure {
protected:
    double _x1, _y1, _x2, _y2, _x3, _y3, _x4, _y4;

public:
    Figure();
    Figure(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;
    virtual ~Figure();

    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;
    
    virtual double square() const = 0;
    virtual void get_center() const = 0; 

    bool operator==(const Figure& other) const;
    virtual operator double() const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Figure& fig);
    friend std::istream& operator>>(std::istream& in, Figure& fig);
};

