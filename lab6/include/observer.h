#pragma once
#include "npc.h"
#include <iostream>
#include <fstream>
#include <memory>

// Text Observer
class TextObserver final : public Observer {
private:
    TextObserver() {}  // Приватный конструктор для Singleton

public:
    // Получение единственного экземпляра
    static std::shared_ptr<Observer> get() {
        static TextObserver instance;
        return std::shared_ptr<Observer>(&instance, [](Observer*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << std::endl << "Battle Report --------" << std::endl;
            std::cout << "Attacker: ";
            attacker->print();
            std::cout << "Defender: ";
            defender->print();
            std::cout << "Result: " << (win ? "Victory" : "Defeat") << std::endl;
        }
    }
};

// File Observer
class FileObserver final : public Observer {
private:
    FileObserver() {}  // Приватный конструктор для Singleton

public:
    // Получение единственного экземпляра
    static std::shared_ptr<Observer> get() {
        static FileObserver instance;
        return std::shared_ptr<Observer>(&instance, [](Observer*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::ofstream fs("log.txt", std::ios::app);
            if (fs.is_open()) {
                fs << std::endl
                   << "Battle Report --------" << std::endl
                   << "Attacker: " << *attacker << std::endl
                   << "Defender: " << *defender << std::endl
                   << "Result: " << (win ? "Victory" : "Defeat") << std::endl;
                fs.close();
            } else {
                std::cerr << "Failed to open log file!" << std::endl;
            }
        }
    }
};
