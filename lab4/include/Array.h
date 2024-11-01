#pragma once
#include <memory>
#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
    std::unique_ptr<std::shared_ptr<T>[]> data;
    size_t capacity;
    size_t size;

public:
    Array(size_t capacity = 10) : capacity(capacity), size(0) {
        data = std::make_unique<std::shared_ptr<T>[]>(capacity);
    }

    void push_back(std::shared_ptr<T> element) {
        if (size >= capacity) {
            reserve(capacity * 2);
        }
        data[size++] = std::move(element);
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) return;
        auto new_data = std::make_unique<std::shared_ptr<T>[]>(new_capacity);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        capacity = new_capacity;
    }

    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }

    std::shared_ptr<T>& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t get_size() const {
        return size;
    }

    void print_all() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << "Figure " << i + 1 << ":" << std::endl;
            std::cout << *data[i];
            std::cout << "Center: " << data[i]->center() << std::endl;
            std::cout << "Area: " << static_cast<double>(*data[i]) << std::endl;
            std::cout << std::endl;
        }
    }
    
    double total_area() const {
        double total = 0;
        for (size_t i = 0; i < size; ++i) {
            total += static_cast<double>(*data[i]);
        }
        return total;
    }
};
