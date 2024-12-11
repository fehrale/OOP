#include "factory.h"
#include "dragon.h"
#include "elf.h"
#include "knight.h"

std::shared_ptr<NPC> factory(std::istream& in) {
    std::string type, name;
    int x, y;
    in >> type >> name >> x >> y;
    std::shared_ptr<NPC> res;
    if (type == "Dragon") {
        res = std::make_shared<Dragon>(x, y, name);
    } else if (type == "Wandering_Knight") {
        res = std::make_shared<Wandering_Knight>(x, y, name);
    } else if (type == "Elf") {
        res = std::make_shared<Elf>(x, y, name);
    } else if (type != "") {
        std::cerr << "Unknown type" << std::endl;
    }
    return res;
}

std::shared_ptr<NPC> factory(const std::string& type, const std::string& name, const int& x, const int& y) {
    std::shared_ptr<NPC> res;
    if (type == "Dragon") {
        res = std::make_shared<Dragon>(x, y, name);
    } else if (type == "Wandering_Knight") {
        res = std::make_shared<Wandering_Knight>(x, y, name);
    } else if (type == "Elf") {
        res = std::make_shared<Elf>(x, y, name);
    } else {
        std::cerr << "Unknown type" << std::endl;
    }
    return res;
}