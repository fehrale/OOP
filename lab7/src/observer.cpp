#include "observer.h"
#include <iostream>
#include <mutex>
#include "npc.h"

std::shared_ptr<IFightObserver> TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        static std::mutex print_mutex;
        std::lock_guard<std::mutex> lck(print_mutex);
        std::cout << std::endl
                  << "Murder --------" << std::endl;
        attacker->print();
        defender->print();
    }
}
