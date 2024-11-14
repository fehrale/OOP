#include <gtest/gtest.h>
#include "../include/FixedMemoryResource.h"
#include "../include/Stack.h"

struct ComplexType {
    int x;
    double y;
    std::string z;

    ComplexType(int x, double y, const std::string& z) : x(x), y(y), z(z) {}

    bool operator==(const ComplexType& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

TEST(StackTest, PushTest) {
    FixedMemoryResource memory_resource(sizeof(Stack<int>::Node), 10);
    Stack<int, std::pmr::polymorphic_allocator<Stack<int>::Node>> stack({&memory_resource});

    stack.push(42);
    EXPECT_EQ(stack.top(), 42);
    EXPECT_EQ(stack.get_size(), 1);
}

TEST(StackTest, PopTest) {
    FixedMemoryResource memory_resource(sizeof(Stack<int>::Node), 10);
    Stack<int, std::pmr::polymorphic_allocator<Stack<int>::Node>> stack({&memory_resource});

    stack.push(10);
    stack.push(20);
    stack.pop();

    EXPECT_EQ(stack.top(), 10);
    EXPECT_EQ(stack.get_size(), 1);
}

TEST(StackTest, TopTest) {
    FixedMemoryResource memory_resource(sizeof(Stack<int>::Node), 10);
    Stack<int, std::pmr::polymorphic_allocator<Stack<int>::Node>> stack({&memory_resource});

    stack.push(100);
    EXPECT_EQ(stack.top(), 100);
}

TEST(StackTest, EmptyTest) {
    FixedMemoryResource memory_resource(sizeof(Stack<int>::Node), 10);
    Stack<int, std::pmr::polymorphic_allocator<Stack<int>::Node>> stack({&memory_resource});

    EXPECT_TRUE(stack.empty());

    stack.push(5);
    EXPECT_FALSE(stack.empty());
}

TEST(StackTest, GetSizeTest) {
    FixedMemoryResource memory_resource(sizeof(Stack<int>::Node), 10);
    Stack<int, std::pmr::polymorphic_allocator<Stack<int>::Node>> stack({&memory_resource});

    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.get_size(), 3);
}

TEST(StackTest, IteratorTest) {
    FixedMemoryResource memory_resource(sizeof(Stack<int>::Node), 10);
    Stack<int, std::pmr::polymorphic_allocator<Stack<int>::Node>> stack({&memory_resource});

    stack.push(10);
    stack.push(20);
    stack.push(30);

    auto it = stack.begin();
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(it, stack.end());
}

TEST(StackTest, ComplexTypeTest) {
    FixedMemoryResource memory_resource(sizeof(Stack<ComplexType>::Node), 10);
    Stack<ComplexType, std::pmr::polymorphic_allocator<Stack<ComplexType>::Node>> stack({&memory_resource});

    ComplexType a{1, 1.1, "one"};
    ComplexType b{2, 2.2, "two"};
    stack.push(a);
    stack.push(b);

    EXPECT_EQ(stack.top(), b);
    stack.pop();
    EXPECT_EQ(stack.top(), a);
}

TEST(FixedMemoryResourceTest, AllocateMemoryTest) {
    FixedMemoryResource memory_resource(128, 10);
    std::pmr::polymorphic_allocator<std::byte> allocator(&memory_resource);

    std::byte* ptr1 = allocator.allocate(128);
    EXPECT_NE(ptr1, nullptr);
    std::byte* ptr2 = allocator.allocate(128);
    EXPECT_NE(ptr2, nullptr);
}

TEST(FixedMemoryResourceTest, ExhaustMemoryTest) {
    FixedMemoryResource memory_resource(128, 2);
    std::pmr::polymorphic_allocator<std::byte> allocator(&memory_resource);

    std::byte* ptr1 = allocator.allocate(128);
    std::byte* ptr2 = allocator.allocate(128);
    std::byte* ptr3 = allocator.allocate(128);

    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(ptr3, nullptr);
}

TEST(FixedMemoryResourceTest, DeallocateMemoryTest) {
    FixedMemoryResource memory_resource(128, 2);
    std::pmr::polymorphic_allocator<std::byte> allocator(&memory_resource);

    std::byte* ptr = allocator.allocate(128);
    EXPECT_NE(ptr, nullptr);

    allocator.deallocate(ptr, 128);
    std::byte* ptr2 = allocator.allocate(128);

    EXPECT_EQ(ptr, ptr2);
}

TEST(FixedMemoryResourceTest, IsEqualTest) {
    FixedMemoryResource resource1(128, 2);
    FixedMemoryResource resource2(128, 2);

    std::pmr::polymorphic_allocator<std::byte> alloc1(&resource1);
    std::pmr::polymorphic_allocator<std::byte> alloc2(&resource2);

    EXPECT_TRUE(resource1.is_equal(resource1));
    EXPECT_FALSE(resource1.is_equal(resource2));
}

