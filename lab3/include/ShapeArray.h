#pragma once

#include "Figure.h"

class ShapeArray {
private:
    Figure** shapes;
    size_t capacity; 
    size_t size; 

    void resize(size_t new_capacity);

public:
    ShapeArray(size_t initial_capacity = 10);
    ~ShapeArray();

    void addShape(Figure* shape);
    void removeShape(size_t index);
    void printShapes() const; 
    double totalArea() const; 
};
