#include "elf.h"
#include "dragon.h"
#include "knight.h"

Elf::Elf(int x, int y)
    : NPC(ElfType, x, y) {}
Elf::Elf(std::istream& is)
    : NPC(ElfType, is) {}

bool Elf::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Elf>(this, [](Elf*) {}));
}

void Elf::print() {
    std::cout << *this;
}

bool Elf::fight(std::shared_ptr<Dragon> other) {
    fight_notify(other, false);
    return true;
}

bool Elf::fight(std::shared_ptr<Wandering_Knight> other) {
    fight_notify(other, true);
    return false;
}

bool Elf::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false);
    return false;
}

void Elf::save(std::ostream& os) {
    os << ElfType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Elf& elf) {
    os << "elf: " << *static_cast<NPC*>(&elf) << std::endl;
    return os;
}