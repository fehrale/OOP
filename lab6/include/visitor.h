#pragma once
#include "npc.h"
#include <memory>
#include "dragon.h"
#include "elf.h"
#include "factory.h"
#include "observer.h"
#include "knight.h"

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Dragon* dragon, NPC* attacker, const int& distance) const = 0;
    virtual void visit(Elf* elf, NPC* attacker, const int& distance) const = 0;
    virtual void visit(Wandering_Knight* knight, NPC* attacker, const int& distance) const = 0;
};

class FightVisitor : public Visitor {
public:
    void visit(Dragon* dragon, NPC* attacker, const int& distance) const override {
        if (dragon->is_alive() && (dynamic_cast<Wandering_Knight*>(attacker) ||
                                   (dynamic_cast<Dragon*>(attacker) && attacker != dragon))) {
            bool win = dragon->is_close(*attacker, distance);
            if (win) {
                dragon->set_alive(false);
            }
            dragon->notify(attacker, win);
        }
    }

    void visit(Elf* elf, NPC* attacker, const int& distance) const override {
        if (elf->is_alive() && dynamic_cast<Dragon*>(attacker)) {
            bool win = elf->is_close(*attacker, distance);
            if (win) {
                elf->set_alive(false);
            }
            elf->notify(attacker, win);
        }
    }

    void visit(Wandering_Knight* knight, NPC* attacker, const int& distance) const override {
        if (knight->is_alive() && (dynamic_cast<Dragon*>(attacker) || dynamic_cast<Elf*>(attacker))) {
            bool win = knight->is_close(*attacker, distance);
            if (win) {
                knight->set_alive(false);
            }
            knight->notify(attacker, win);
        }
    }
};
