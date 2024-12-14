#include "knight.h"
#include "dragon.h"
#include "elf.h"

Wandering_Knight::Wandering_Knight(int x, int y)
    : NPC(KnightType, x, y) {}
Wandering_Knight::Wandering_Knight(std::istream& is)
    : NPC(KnightType, is) {}

bool Wandering_Knight::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Wandering_Knight>(this, [](Wandering_Knight*) {}));
}

void Wandering_Knight::print() {
    std::cout << *this;
}

bool Wandering_Knight::fight(std::shared_ptr<Dragon> other) {
    fight_notify(other, true);
    return true;
}

bool Wandering_Knight::fight(std::shared_ptr<Wandering_Knight> other) {
    fight_notify(other, false);
    return false;
}

bool Wandering_Knight::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false);
    return true;
}

void Wandering_Knight::save(std::ostream& os) {
    os << KnightType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Wandering_Knight& wandering_knight) {
    os << "wandering knight: " << *static_cast<NPC*>(&wandering_knight) << std::endl;
    return os;
}