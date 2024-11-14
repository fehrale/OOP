#include <memory_resource>
#include <stdexcept>

template <typename T, typename Alloc = std::pmr::polymorphic_allocator<std::byte>>
class Stack {
public:
    struct Node {
        T data;
        Node* next;
    };

    explicit Stack(const Alloc& alloc = Alloc()) : allocator(alloc), head(nullptr), size(0) {}

    ~Stack() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            allocator.deallocate(tmp, 1);
        }
    }

    void push(const T& value) {
        Node* new_node = allocator.allocate(1);
        new_node->data = value;
        new_node->next = head;
        head = new_node;
        ++size;
    }

    void pop() {
        if (!head) throw std::runtime_error("Stack is empty");
        Node* tmp = head;
        head = head->next;
        allocator.deallocate(tmp, 1);
        --size;
    }

    T& top() const {
        if (!head) throw std::runtime_error("Stack is empty");
        return head->data;
    }

    bool empty() const {
        return head == nullptr;
    }

    std::size_t get_size() const {
        return size;
    }

    struct Iterator {
        Node* current;

        Iterator(Node* node) : current(node) {}

        T& operator*() const { return current->data; }
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }

        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

private:
    std::pmr::polymorphic_allocator<Node> allocator;
    Node* head;
    std::size_t size;
};
