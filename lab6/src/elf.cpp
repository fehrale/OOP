#include "elf.h"
#include <algorithm>
#include "dragon.h"
#include "knight.h"
#include "visitor.h"

Elf::Elf(const int& _x, const int& _y, const std::string& _name) {
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Elf::print(std::ostream& out) {
    out << *this;
}

void Elf::accept(NPC* attacker, const int& distance) {
    if (alive && dynamic_cast<Dragon*>(attacker)) {
        bool win = is_close(*attacker, distance);
        if (win)
            alive = false;
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Elf& other) {
    return out << "Elf " << other.name << " {" << other.x << ", " << other.y << '}';
}

void Elf::accept(const Visitor& visitor, NPC* attacker, const int& distance) {
    visitor.visit(this, attacker, distance);
}