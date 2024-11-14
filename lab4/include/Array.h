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
    Array(size_t initial_capacity = 10) 
        : capacity(initial_capacity), size(0) {
        data = std::make_unique<std::shared_ptr<T>[]>(capacity);
    }

    void push_back(const std::shared_ptr<T>& element) {
        if (size == capacity) {
            reserve(static_cast<size_t>(capacity * 2) + 1);
        }
        data[size++] = element;
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

    void shrink_to_fit() {
        if (size == capacity) return;
        auto new_data = std::make_unique<std::shared_ptr<T>[]>(size);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        capacity = size;
    }

    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        data[index].reset();
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        data[size - 1].reset();
        --size;
    }

    std::shared_ptr<T>& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const std::shared_ptr<T>& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t get_size() const { return size; }

    void print_all() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << "Figure " << i + 1 << ":\n" << *data[i];
                std::cout << "Center: " << data[i]->center() << "\n";
                std::cout << "Area: " << static_cast<double>(*data[i]) << "\n\n";
            }
        }
    }

    double total_area() const {
        double total = 0;
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                total += static_cast<double>(*data[i]);
            }
        }
        return total;
    }
};
