#include "dragon.h"

Dragon::Dragon(const std::string& name, int x, int y) : NPC(NpcType::DragonType, name, x, y) {}
Dragon::Dragon(std::istream& is) : NPC(NpcType::DragonType, is) {}

bool Dragon::accept(const std::shared_ptr<NPC>& attacker) const {
    // Дракон убивает всех
    bool result = true;
    attacker->fight_notify(std::const_pointer_cast<NPC>(shared_from_this()), result);
    return result;
}

void Dragon::print() {
    std::cout << *this;
}

void Dragon::save(std::ostream& os) {
    os << NpcType::DragonType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Dragon& dragon) {
    os << "Dragon " << *static_cast<NPC*>(&dragon) << std::endl;
    return os;
}
