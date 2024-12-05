#pragma once
#include "npc.h"
#include "visitor.h"

class Knight final : public NPC {
public:
    Knight(const std::string&, int, int);
    Knight(std::istream&);

    virtual bool accept(const std::shared_ptr<NPC>&) const override;

    void print() override;
    void save(std::ostream&) override;

    friend std::ostream& operator<<(std::ostream&, Knight&);
};
