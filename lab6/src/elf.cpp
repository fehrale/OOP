#include "elf.h"

Elf::Elf(const std::string& name, int x, int y) : NPC(ElfType, name, x, y) {}
Elf::Elf(std::istream& is) : NPC(ElfType, is) {}

bool Elf::accept(const std::shared_ptr<NPC>& attacker) const {
    // Эльф убивает только странствующих рыцарей
    if (attacker->get_type() == NpcType::KnightType) {
        attacker->fight_notify(std::const_pointer_cast<NPC>(shared_from_this()), true);
        return true;
    }
    return false;
}

void Elf::print() {
    std::cout << *this;
}

void Elf::save(std::ostream& os) {
    os << ElfType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Elf& Elf) {
    os << "Elf " << *static_cast<NPC*>(&Elf) << std::endl;
    return os;
}
