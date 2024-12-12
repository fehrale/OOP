#include "knight.h"
#include <algorithm>
#include "dragon.h"
#include "elf.h"
#include "visitor.h"

Wandering_Knight::Wandering_Knight(const int& _x, const int& _y, const std::string& _name) {
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Wandering_Knight::print(std::ostream& out) {
    out << *this;
}

// void Wandering_Knight::accept(NPC* attacker, const int& distance) {
//     if (alive && (dynamic_cast<Dragon*>(attacker) || dynamic_cast<Elf*>(attacker))) {
//         bool win = is_close(*attacker, distance);
//         if (win)
//             alive = false;
//         notify(attacker, win);
//     }
// }

std::ostream& operator<<(std::ostream& out, const Wandering_Knight& other) {
    return out << "Wandering Knight " << other.name << " {" << other.x << ", " << other.y << '}';
}

void Wandering_Knight::accept(const Visitor& visitor, NPC* attacker, const int& distance) {
    visitor.visit(this, attacker, distance);
}
