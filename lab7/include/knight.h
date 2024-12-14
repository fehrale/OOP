#pragma once
#include "npc.h"

struct Wandering_Knight : public NPC {
    Wandering_Knight(int x, int y);
    Wandering_Knight(std::istream& is);

    void print() override;

    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Wandering_Knight> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool accept(std::shared_ptr<NPC> visitor) override;

    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Wandering_Knight& wandering_knight);
};