#pragma once
#include "npc.h"

class Dragon : public NPC {
   public:
    Dragon(const int&, const int&, const std::string&);

    void print(std::ostream&) override;

    void accept(NPC*, const int&) override;

    friend std::ostream& operator<<(std::ostream&, const Dragon&);

    void accept(const Visitor& visitor, NPC* attacker, const int& distance) override;
};