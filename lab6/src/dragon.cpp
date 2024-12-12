#include "dragon.h"
#include <algorithm>
#include "elf.h"
#include "knight.h"
#include "visitor.h"

Dragon::Dragon(const int& _x, const int& _y, const std::string& _name) {
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Dragon::print(std::ostream& out) {
    out << *this;
}

std::ostream& operator<<(std::ostream& out, const Dragon& other) {
    return out << "Dragon " << other.name << " {" << other.x << ", " << other.y << '}';
}

void Dragon::accept(const Visitor& visitor, NPC* attacker, const int& distance) {
    visitor.visit(this, attacker, distance);
}
