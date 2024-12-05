#include "knight.h"

Knight::Knight(const std::string& name, int x, int y) : NPC(NpcType::KnightType, name, x, y) {}
Knight::Knight(std::istream& is) : NPC(NpcType::KnightType, is) {}

bool Knight::accept(const std::shared_ptr<NPC>& attacker) const {
    // Рыцарь убивает только драконов
    if (attacker->get_type() == NpcType::DragonType) {
        attacker->fight_notify(std::const_pointer_cast<NPC>(shared_from_this()), true);
        return true;
    }
    return false;
}

void Knight::print() {
    std::cout << *this;
}

void Knight::save(std::ostream& os) {
    os << NpcType::KnightType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Knight& knight) {
    os << "Knight " << *static_cast<NPC*>(&knight) << std::endl;
    return os;
}
