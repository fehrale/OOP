#pragma once
#include "npc.h"
#include "visitor.h"

class Dragon final : public NPC {
public:
    Dragon(const std::string&, int, int);
    Dragon(std::istream&);

    virtual bool accept(const std::shared_ptr<NPC>&) const override;

    void print() override;
    void save(std::ostream&) override;

    friend std::ostream& operator<<(std::ostream&, Dragon&);
};
