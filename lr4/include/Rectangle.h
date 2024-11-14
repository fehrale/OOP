#pragma once
#include "Figure.h"

template <Scalar T>
class Rectangle : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;

public:
    Rectangle(const Point<T>& bottom_left, T width, T height) {
        vertices = std::make_unique<Point<T>[]>(4);
        vertices[0] = bottom_left;
        vertices[1] = Point<T>(bottom_left.x + width, bottom_left.y);
        vertices[2] = Point<T>(bottom_left.x + width, bottom_left.y + height);
        vertices[3] = Point<T>(bottom_left.x, bottom_left.y + height);
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
        T width = std::abs(vertices[0].x - vertices[1].x);
        T height = std::abs(vertices[0].y - vertices[3].y);
        return static_cast<double>(width * height);
    }

    Rectangle(const Rectangle& other) {
        vertices = std::make_unique<Point<T>[]>(4);
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
    }

    Rectangle(Rectangle&& other) noexcept : vertices(std::move(other.vertices)) {}

    Rectangle& operator=(const Rectangle& other) {
        if (this == &other) return *this;
        vertices = std::make_unique<Point<T>[]>(4);
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
        return *this;
    }

    Rectangle& operator=(Rectangle&& other) noexcept {
        if (this == &other) return *this;
        vertices = std::move(other.vertices);
        return *this;
    }

    bool operator==(const Rectangle& other) const {
        for (int i = 0; i < 4; ++i) {
            if (vertices[i] != other.vertices[i]) return false;
        }
        return true;
    }
};
