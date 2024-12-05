#pragma once
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <string>

class NPC;
class Elf;
class Dragon;
class Knight;

using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType {
    UnknownType,
    ElfType,
    DragonType,
    KnightType,
};

class Observer {
public:
    virtual void on_fight(const std::shared_ptr<NPC>, const std::shared_ptr<NPC>, bool) = 0;
};

class Visitor;

class NPC : public std::enable_shared_from_this<NPC> {
protected:
    NpcType type;
    std::string name{""};
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<Observer>> observers;

public:
    NPC(NpcType, const std::string&, int, int);
    NPC(NpcType, std::istream&);

    NpcType get_type() const {
        return type;
    }

    virtual bool accept(const std::shared_ptr<NPC>&) const = 0;

    void subscribe(const std::shared_ptr<Observer>&);
    void fight_notify(const std::shared_ptr<NPC>, bool) const;
    virtual bool is_close(const std::shared_ptr<NPC>&, size_t) const;

    virtual void print() = 0;
    virtual void save(std::ostream&);

    friend std::ostream& operator<<(std::ostream&, NPC&);
};