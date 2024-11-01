#pragma once
#include "Figure.h"
#include <cmath>

template <Scalar T>
class Trapezoid : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;

public:
    Trapezoid(const Point<T>& v1, const Point<T>& v2, const Point<T>& v3, const Point<T>& v4) {
        vertices = std::make_unique<Point<T>[]>(4);
        vertices[0] = v1;
        vertices[1] = v2;
        vertices[2] = v3;
        vertices[3] = v4;
    }

    Point<T> center() const override {
        T cx = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / 4;
        T cy = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / 4;
        return Point<T>(cx, cy);
    }

    void print(std::ostream& os) const override {
        for (int i = 0; i < 4; ++i) {
            os << "Vertex " << i + 1 << ": " << vertices[i] << std::endl;
        }
    }

    operator double() const override {
        T a = std::abs(vertices[1].x - vertices[0].x);
        T b = std::abs(vertices[3].x - vertices[2].x);
        T height = std::abs(vertices[0].y - vertices[2].y);
        return static_cast<double>((a + b) * height / 2);
    }

    Trapezoid(const Trapezoid& other) {
        vertices = std::make_unique<Point<T>[]>(4);
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
    }

    Trapezoid(Trapezoid&& other) noexcept : vertices(std::move(other.vertices)) {}

    Trapezoid& operator=(const Trapezoid& other) {
        if (this == &other) return *this;
        vertices = std::make_unique<Point<T>[]>(4);
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
        return *this;
    }

    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this == &other) return *this;
        vertices = std::move(other.vertices);
        return *this;
    }

    bool operator==(const Trapezoid& other) const {
        for (int i = 0; i < 4; ++i) {
            if (vertices[i] != other.vertices[i]) return false;
        }
        return true;
    }
};
