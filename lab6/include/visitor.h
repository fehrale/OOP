#pragma once
#include "npc.h"

class Visitor {
public:
    virtual bool visit(const std::shared_ptr<NPC>&) const = 0;
};

class ElfVisitor final : public Visitor {
public:
    bool visit(const std::shared_ptr<NPC>& npc) const override {
        return npc->get_type() == NpcType::KnightType;  // Эльф атакует рыцарей
    }
};

class DragonVisitor final : public Visitor {
public:
    bool visit(const std::shared_ptr<NPC>& npc) const override {
        return true;  // Дракон атакует всех
    }
};

class KnightVisitor final : public Visitor {
public:
    bool visit(const std::shared_ptr<NPC>& npc) const override {
        return npc->get_type() == NpcType::DragonType;  // Рыцарь атакует драконов
    }
};

class VisitorFactory {
public:
    static std::shared_ptr<Visitor> CreateVisitor(const NpcType& type) {
        switch (type) {
            case NpcType::ElfType:
                return std::make_shared<ElfVisitor>();
            case NpcType::DragonType:
                return std::make_shared<DragonVisitor>();
            case NpcType::KnightType:
                return std::make_shared<KnightVisitor>();
            default:
                return nullptr;
        }
    }
};
