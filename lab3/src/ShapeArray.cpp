#include "../include/ShapeArray.h"
#include <iostream>

ShapeArray::ShapeArray(size_t initial_capacity) : capacity(initial_capacity), size(0) {
    shapes = new Figure*[capacity];
}

ShapeArray::~ShapeArray() {
    for (size_t i = 0; i < size; ++i) {
        delete shapes[i];
    }
    delete[] shapes;
}

void ShapeArray::resize(size_t new_capacity) {
    Figure** new_shapes = new Figure*[new_capacity];
    for (size_t i = 0; i < size; ++i) {
        new_shapes[i] = shapes[i];
    }
    delete[] shapes;
    shapes = new_shapes;
    capacity = new_capacity;
}

void ShapeArray::addShape(Figure* shape) {
    if (size >= capacity) {
        resize(capacity * 2);
    }
    shapes[size++] = shape;
}

void ShapeArray::removeShape(size_t index) {
    if (index >= size || shapes[index] == nullptr) {
        std::cerr << "Index out of bounds or shape already deleted. Unable to remove shape." << std::endl;
        return;
    }

    delete shapes[index];

    for (size_t i = index; i < size - 1; ++i) {
        shapes[i] = shapes[i + 1];
    }

    --size;
    shapes[size] = nullptr;
}

void ShapeArray::printShapes() const {
    for (size_t i = 0; i < size; ++i) {
        std::cout << *shapes[i]; 
    }
}

double ShapeArray::totalArea() const {
    double total = 0.0;
    for (size_t i = 0; i < size; ++i) {
        total += shapes[i]->square();
    }
    return total;
}
