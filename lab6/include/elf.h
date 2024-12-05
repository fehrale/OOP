#pragma once
#include "npc.h"
#include "visitor.h"

class Elf final : public NPC {
public:
    Elf(const std::string&, int, int);
    Elf(std::istream&);

    virtual bool accept(const std::shared_ptr<NPC>&) const override;

    void print() override;
    void save(std::ostream&) override;

    friend std::ostream& operator<<(std::ostream&, Elf&);
};
