#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <vector>
#include "npc.h"
#include "dragon.h"
#include "elf.h"
#include "factory.h"
#include "knight.h"
#include "visitor.h"

TEST(Constructors, Dragon) {
    Dragon s(0, 0, "Belthromar");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Dragon Belthromar {0, 0}");
}

TEST(Constructors, Wandering_Knight) {
    Wandering_Knight t(1, 1, "Emilia");
    std::stringstream out;
    t.print(out);
    ASSERT_EQ(out.str(), "Wandering Knight Emilia {1, 1}");
}

TEST(Constructors, Elf) {
    Elf e(2, 2, "Dobby");
    std::stringstream out;
    e.print(out);
    ASSERT_EQ(out.str(), "Elf Dobby {2, 2}");
}

TEST(Factory, basic) {
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Dragon", "Belthromar", 0, 0));
    persons.push_back(factory("Wandering_Knight", "Emilia", 1, 1));
    persons.push_back(factory("Elf", "Dobby", 2, 2));

    std::stringstream out;

    for (auto& elem : persons) {
        elem->print(out);
    }

    ASSERT_EQ(out.str(), "Dragon Belthromar {0, 0}Wandering Knight Emilia {1, 1}Elf Dobby {2, 2}");
}

std::unique_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Dragon") {
        return std::make_unique<Dragon>(x, y, name);
    } else if (type == "Elf") {
        return std::make_unique<Elf>(x, y, name);
    } else if (type == "Wandering_Knight") {
        return std::make_unique<Wandering_Knight>(x, y, name);
    }
    throw std::invalid_argument("Unknown NPC type");
}

class VisitorTest : public ::testing::Test {
protected:
    FightVisitor visitor;
};

TEST_F(VisitorTest, DragonFightsKnight) {
    auto dragon = createNPC("Dragon", "Belthromar", 0, 0);
    auto knight = createNPC("Wandering_Knight", "Emilia", 3, 4);

    EXPECT_TRUE(dragon->is_alive());
    EXPECT_TRUE(knight->is_alive());

    visitor.visit(static_cast<Dragon*>(dragon.get()), knight.get(), 5);

    EXPECT_FALSE(dragon->is_alive());
    EXPECT_TRUE(knight->is_alive());
}

TEST_F(VisitorTest, ElfFightsDragon) {
    auto elf = createNPC("Elf", "Dobby", 4, 4);
    auto dragon = createNPC("Dragon", "Alsiel", 5, 5);

    EXPECT_TRUE(elf->is_alive());
    EXPECT_TRUE(dragon->is_alive());

    visitor.visit(static_cast<Elf*>(elf.get()), dragon.get(), 2);

    EXPECT_FALSE(elf->is_alive());
    EXPECT_TRUE(dragon->is_alive());
}

TEST_F(VisitorTest, KnightFightsElf) {
    auto knight = createNPC("Wandering_Knight", "Arthur", 1, 1);
    auto elf = createNPC("Elf", "Legolas", 2, 2);

    EXPECT_TRUE(knight->is_alive());
    EXPECT_TRUE(elf->is_alive());

    visitor.visit(static_cast<Wandering_Knight*>(knight.get()), elf.get(), 5);

    EXPECT_FALSE(knight->is_alive());
    EXPECT_TRUE(elf->is_alive());
}

TEST_F(VisitorTest, FightBeyondDistance) {
    auto dragon = createNPC("Dragon", "Belthromar", 0, 0);
    auto knight = createNPC("Wandering_Knight", "Emilia", 10, 10);

    EXPECT_TRUE(dragon->is_alive());
    EXPECT_TRUE(knight->is_alive());

    visitor.visit(static_cast<Dragon*>(dragon.get()), knight.get(), 5);

    EXPECT_TRUE(dragon->is_alive());
    EXPECT_TRUE(knight->is_alive());
}

TEST_F(VisitorTest, SelfAttackIgnored) {
    auto dragon = createNPC("Dragon", "Belthromar", 0, 0);

    EXPECT_TRUE(dragon->is_alive());

    visitor.visit(static_cast<Dragon*>(dragon.get()), dragon.get(), 5);

    EXPECT_TRUE(dragon->is_alive());
}

TEST_F(VisitorTest, SequentialFights) {
    auto dragon = createNPC("Dragon", "Alsiel", 3, 3);
    auto elf = createNPC("Elf", "Dobby", 1, 1);
    auto knight = createNPC("Wandering_Knight", "Emilia", 2, 2);

    EXPECT_TRUE(dragon->is_alive());
    EXPECT_TRUE(elf->is_alive());
    EXPECT_TRUE(knight->is_alive());

    visitor.visit(static_cast<Dragon*>(dragon.get()), elf.get(), 3);
    EXPECT_TRUE(elf->is_alive());
    EXPECT_TRUE(dragon->is_alive());

    visitor.visit(static_cast<Wandering_Knight*>(knight.get()), dragon.get(), 3);
    EXPECT_TRUE(dragon->is_alive());
    EXPECT_FALSE(knight->is_alive());
}