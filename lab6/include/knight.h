#pragma once
#include "npc.h"

class Wandering_Knight : public NPC {
   public:
    Wandering_Knight(const int&, const int&, const std::string&);

    void print(std::ostream&) override;

    void accept(NPC*, const int&) override;

    friend std::ostream& operator<<(std::ostream&, const Wandering_Knight&);

    void accept(const Visitor& visitor, NPC* attacker, const int& distance) override;
};