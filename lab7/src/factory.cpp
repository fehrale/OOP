#include "factory.h"
#include <iostream>
#include "dragon.h"
#include "elf.h"
#include "knight.h"
#include "npc.h"
#include "observer.h"

std::shared_ptr<NPC> factory(std::istream& is) {
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type) {
        switch (type) {
            case DragonType:
                result = std::make_shared<Dragon>(is);
                break;
            case KnightType:
                result = std::make_shared<Wandering_Knight>(is);
                break;
            case ElfType:
                result = std::make_shared<Elf>(is);
                break;
            default:
                std::cerr << "unexpected NPC type:" << type << std::endl;
                return nullptr;
        }
    }

    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
        case DragonType:
            result = std::make_shared<Dragon>(x, y);
            break;
        case KnightType:
            result = std::make_shared<Wandering_Knight>(x, y);
            break;
        case ElfType:
            result = std::make_shared<Elf>(x, y);
            break;
        default:
            break;
    }
    if (result)
        result->subscribe(TextObserver::get());

    return result;
}
