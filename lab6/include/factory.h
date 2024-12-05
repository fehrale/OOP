#pragma once
#include "dragon.h"
#include "npc.h"
#include "observer.h"
#include "elf.h"
#include "knight.h"

class Factory {
public:
    static std::shared_ptr<NPC> CreateNPC(const NpcType& type, const std::string& name, int x, int y) {
        std::shared_ptr<NPC> result;
        switch (type) {
            case NpcType::ElfType:
                result = std::make_shared<Elf>(name, x, y);
                break;

            case NpcType::DragonType:
                result = std::make_shared<Dragon>(name, x, y);
                break;

            case NpcType::KnightType:
                result = std::make_shared<Knight>(name, x, y);
                break;

            default:
                break;
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }

    static std::shared_ptr<NPC> CreateNPC(std::istream& is) {
        std::shared_ptr<NPC> result;
        int type{0};
        if (is >> type) {
            switch (type) {
                case NpcType::ElfType:
                    result = std::make_shared<Elf>(is);
                    break;

                case NpcType::DragonType:
                    result = std::make_shared<Dragon>(is);
                    break;

                case NpcType::KnightType:
                    result = std::make_shared<Knight>(is);
                    break;

                default:
                    break;
            }
        } else {
            std::cerr << "Unexpected NPC type:" << type << std::endl;
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }
};
