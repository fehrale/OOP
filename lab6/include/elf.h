#pragma once
#include "npc.h"

class Elf : public NPC {
   public:
    Elf(const int&, const int&, const std::string&);

    void print(std::ostream&) override;

    friend std::ostream& operator<<(std::ostream&, const Elf&);

    void accept(const Visitor& visitor, NPC* attacker, const int& distance) override;
};