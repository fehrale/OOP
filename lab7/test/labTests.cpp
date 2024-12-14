#include <gtest/gtest.h>
#include <memory>
#include "dragon.h"
#include "elf.h"
#include "npc.h"
#include "knight.h"
#include "factory.h"
#include "observer.h"
#include <gtest/gtest.h>
#include <fstream>
#include <memory>
#include <set>
#include <sstream>

TEST(elf_constructor, test1) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);

    EXPECT_EQ((a->position()).first, 100);
}

TEST(elf_constructor, test2) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);

    EXPECT_EQ((a->position()).second, 100);
}

TEST(elf_constructor, test3) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);
    EXPECT_EQ(ElfType, a->get_type());
}

TEST(elf_constructor, test4) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);
    EXPECT_TRUE(a->is_alive());
}

TEST(elf_constructor, test5) {
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Elf>(x2, y2);
    EXPECT_TRUE(a->is_close(b, 100));
}

TEST(elf_constructor, test6) {
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);

    a->move(50, 50, 100, 100);
    EXPECT_EQ((a->position()).first, 60);
}

TEST(dragon_constructor, test1) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);

    EXPECT_EQ((a->position()).first, 100);
}

TEST(dragon_constructor, test2) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);

    EXPECT_EQ((a->position()).second, 100);
}

TEST(dragon_constructor, test3) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);
    EXPECT_EQ(DragonType, a->get_type());
}

TEST(dragon_constructor, test4) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);
    EXPECT_TRUE(a->is_alive());
}

TEST(dragon_constructor, test5) {
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Dragon>(x2, y2);
    EXPECT_TRUE(a->is_close(b, 100));
}

TEST(dragon_constructor, test6) {
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);

    a->move(50, 50, 100, 100);
    EXPECT_EQ((a->position()).first, 60);
}

TEST(knight_constructor, test1) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);

    EXPECT_EQ((a->position()).first, 100);
}

TEST(knight_constructor, test2) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);

    EXPECT_EQ((a->position()).second, 100);
}

TEST(knight_constructor, test3) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);
    EXPECT_EQ(KnightType, a->get_type());
}

TEST(knight_constructor, test4) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);
    EXPECT_TRUE(a->is_alive());
}

TEST(knight_constructor, test5) {
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Wandering_Knight>(x2, y2);
    EXPECT_TRUE(a->is_close(b, 100));
}

TEST(knight_constructor, test6) {
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);

    a->move(50, 50, 100, 100);
    EXPECT_EQ((a->position()).first, 60);
}

TEST(factory_test, create_dragon) {
    auto npc = factory(DragonType, 10, 20);
    ASSERT_TRUE(npc != nullptr);
    EXPECT_EQ(npc->get_type(), DragonType);
    EXPECT_EQ(npc->position(), std::make_pair(10, 20));
}

TEST(factory_test, create_elf) {
    auto npc = factory(ElfType, 30, 40);
    ASSERT_TRUE(npc != nullptr);
    EXPECT_EQ(npc->get_type(), ElfType);
    EXPECT_EQ(npc->position(), std::make_pair(30, 40));
}

TEST(factory_test, create_knight) {
    auto npc = factory(KnightType, 50, 60);
    ASSERT_TRUE(npc != nullptr);
    EXPECT_EQ(npc->get_type(), KnightType);
    EXPECT_EQ(npc->position(), std::make_pair(50, 60));
}

TEST(observer_test, notify_on_fight) {
    auto dragon = factory(DragonType, 10, 10);
    auto knight = factory(KnightType, 10, 15);

    std::stringstream ss;
    std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

    dragon->accept(knight);

    EXPECT_TRUE(ss.str().find("Murder") != std::string::npos);
    std::cout.rdbuf(old_cout); // Восстановление стандартного потока вывода
}

TEST(grid_test, display_grid) {
    set_t npcs;
    npcs.insert(factory(DragonType, 10, 10));
    npcs.insert(factory(ElfType, 20, 20));
    npcs.insert(factory(KnightType, 30, 30));

    std::stringstream ss;
    std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

    std::array<char, 20 * 20> grid{0};
    for (const auto& npc : npcs) {
        auto [x, y] = npc->position();
        int index = x / 5 + 20 * (y / 5);
        grid[index] = npc->get_type() == DragonType ? 'D' : (npc->get_type() == ElfType ? 'E' : 'K');
    }

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (grid[i * 20 + j]) {
                std::cout << "[" << grid[i * 20 + j] << "]";
            } else {
                std::cout << "[ ]";
            }
        }
        std::cout << std::endl;
    }

    std::cout.rdbuf(old_cout);

    EXPECT_TRUE(ss.str().find("[D]") != std::string::npos);
    EXPECT_TRUE(ss.str().find("[E]") != std::string::npos);
    EXPECT_TRUE(ss.str().find("[K]") != std::string::npos);
}
