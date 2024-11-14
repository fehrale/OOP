#include <memory_resource>
#include <vector>
#include <cassert>

class FixedMemoryResource : public std::pmr::memory_resource {
private:
    std::vector<std::byte> memory_pool;
    std::vector<void*> free_blocks;
    size_t block_size;
    size_t blocks_count;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        if (bytes > block_size || free_blocks.empty()) {
            return nullptr;
        }
        void* ptr = free_blocks.back();
        free_blocks.pop_back();
        return ptr;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        if (bytes <= block_size) {
            free_blocks.push_back(p);
        }
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

public:
    FixedMemoryResource(size_t block_size, size_t blocks_count)
        : block_size(block_size), blocks_count(blocks_count), memory_pool(block_size * blocks_count) {
        for (size_t i = 0; i < blocks_count; ++i) {
            free_blocks.push_back(&memory_pool[i * block_size]);
        }
    }

    ~FixedMemoryResource() {
        free_blocks.clear();
        memory_pool.clear();
    }
};
