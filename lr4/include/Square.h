#pragma once
#include "Figure.h"
#include <cmath>

template <Scalar T>
class Square : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;

public:
    Square(const Point<T>& bottom_left, T side_length) {
        vertices = std::make_unique<Point<T>[]>(4);
        vertices[0] = bottom_left;
        vertices[1] = Point<T>(bottom_left.x + side_length, bottom_left.y);
        vertices[2] = Point<T>(bottom_left.x + side_length, bottom_left.y + side_length);
        vertices[3] = Point<T>(bottom_left.x, bottom_left.y + side_length);
    }

    Point<T> center() const override {
        T cx = (vertices[0].x + vertices[2].x) / 2;
        T cy = (vertices[0].y + vertices[2].y) / 2;
        return Point<T>(cx, cy);
    }

    void print(std::ostream& os) const override {
        for (int i = 0; i < 4; ++i) {
            os << "Vertex " << i + 1 << ": " << vertices[i] << std::endl;
        }
    }

    operator double() const override {
        T side_length = std::abs(vertices[0].x - vertices[1].x);
        return static_cast<double>(side_length * side_length);
    }

    Square(const Square& other) {
        vertices = std::make_unique<Point<T>[]>(4);
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
    }

    Square(Square&& other) noexcept : vertices(std::move(other.vertices)) {}

    Square& operator=(const Square& other) {
        if (this == &other) return *this;
        vertices = std::make_unique<Point<T>[]>(4);
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
        return *this;
    }

    Square& operator=(Square&& other) noexcept {
        if (this == &other) return *this;
        vertices = std::move(other.vertices);
        return *this;
    }

    bool operator==(const Square& other) const {
        for (int i = 0; i < 4; ++i) {
            if (vertices[i] != other.vertices[i]) return false;
        }
        return true;
    }
};
