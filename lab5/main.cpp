#include <iostream>
#include "include/FixedMemoryResource.h"
#include "include/Stack.h"

struct ComplexType {
    int x;
    double y;
    std::string z;

    ComplexType(int x, double y, const std::string& z) : x(x), y(y), z(z) {}
};

int main() {
    FixedMemoryResource memory_resource(sizeof(Stack<int>::Node), 10);
    std::pmr::polymorphic_allocator<std::byte> alloc(&memory_resource);
    Stack<int, std::pmr::polymorphic_allocator<Stack<int>::Node>> int_stack(alloc);

    for (int i = 1; i <= 5; ++i) {
        int_stack.push(i);
    }

    std::cout << "Stack of int values: ";
    for (auto it = int_stack.begin(); it != int_stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    FixedMemoryResource complex_memory_resource(sizeof(Stack<ComplexType>::Node), 10);
    std::pmr::polymorphic_allocator<std::byte> complex_alloc(&complex_memory_resource);
    Stack<ComplexType, std::pmr::polymorphic_allocator<Stack<ComplexType>::Node>> complex_stack(complex_alloc);

    complex_stack.push(ComplexType{1, 1.1, "one"});
    complex_stack.push(ComplexType{2, 2.2, "two"});

    std::cout << "Stack of ComplexType values:\n";
    for (auto it = complex_stack.begin(); it != complex_stack.end(); ++it) {
        std::cout << "ComplexType{x: " << (*it).x << ", y: " << (*it).y << ", z: " << (*it).z << "}\n";
    }

    return 0;
}
