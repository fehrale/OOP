#include <array>
#include <chrono>
#include <mutex>
#include <optional>
#include <queue>
#include <sstream>
#include <thread>
#include "dragon.h"
#include "elf.h"
#include "npc.h"
#include "knight.h"
#include "factory.h"
#include "observer.h"

using namespace std::chrono_literals;
std::mutex print_mutex;

std::ostream& operator<<(std::ostream& os, const set_t& array) {
    for (auto& n : array)
        n->print();
    return os;
}

set_t fight(const set_t& array, size_t distance) {
    set_t dead_list;

    for (const auto& attacker : array)
        for (const auto& defender : array)
            if ((attacker != defender) &&
                attacker->is_close(defender, distance) &&
                defender->accept(attacker))
                dead_list.insert(defender);

    return dead_list;
}

struct print : std::stringstream {
    ~print() {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lck(print_mutex);
        std::cout << this->str();
        std::cout.flush();
    }
};

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
   private:
    std::queue<FightEvent> events;
    std::shared_mutex mtx;

    FightManager() {}

   public:
    static FightManager& get() {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent&& event) {
        std::lock_guard<std::shared_mutex> lock(mtx);
        events.push(event);
    }

    void operator()() {
        while (true) {
            {
                std::optional<FightEvent> event;

                {
                    std::lock_guard<std::shared_mutex> lock(mtx);
                    if (!events.empty()) {
                        event = events.back();
                        events.pop();
                    }
                }

                if (event) {
                    try {
                        if (event->attacker->is_alive())
                            if (event->defender->is_alive())
                                if (event->defender->accept(event->attacker))
                                    event->defender->must_die();
                    } catch (...) {
                        std::lock_guard<std::shared_mutex> lock(mtx);
                        events.push(*event);
                    }
                } else
                    std::this_thread::sleep_for(100ms);
            }
        }
    }
};

int main() {
    set_t array;
    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE{40};

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 50; ++i) {
        array.insert(factory(NpcType(std::rand() % 3 + 1), std::rand() % MAX_X, std::rand() % MAX_Y));
    }

    std::cout << "Starting list:" << std::endl << array;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&array, MAX_X, MAX_Y, DISTANCE]() {
        while (true) {
            for (std::shared_ptr<NPC> npc : array) {
                if (npc->is_alive()) {
                    int shift_x = std::rand() % 20 - 10;
                    int shift_y = std::rand() % 20 - 10;
                    npc->move(shift_x, shift_y, MAX_X, MAX_Y);
                }
            }
            for (std::shared_ptr<NPC> npc : array) {
                for (std::shared_ptr<NPC> other : array) {
                    if (other != npc && npc->is_alive() && other->is_alive() &&
                        npc->is_close(other, DISTANCE)) {
                        FightManager::get().add_event({npc, other});
                    }
                }
            }
            std::this_thread::sleep_for(1s);
        }
    });

    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start_time < 30s) {
        const int grid{20}, step_x{MAX_X / grid}, step_y{MAX_Y / grid};
        {
            std::array<char, grid * grid> fields{0};
            for (std::shared_ptr<NPC> npc : array) {
                auto [x, y] = npc->position();
                int i = x / step_x;
                int j = y / step_y;

                if (npc->is_alive()) {
                    switch (npc->get_type()) {
                        case DragonType:
                            fields[i + grid * j] = 'D';
                            break;
                        case KnightType:
                            fields[i + grid * j] = 'K';
                            break;
                        case ElfType:
                            fields[i + grid * j] = 'E';
                            break;
                        default:
                            break;
                    }
                } else {
                    fields[i + grid * j] = '.';
                }
            }

            std::lock_guard<std::mutex> lck(print_mutex);
            for (int j = 0; j < grid; ++j) {
                for (int i = 0; i < grid; ++i) {
                    char c = fields[i + j * grid];
                    if (c != 0)
                        std::cout << "[" << c << "]";
                    else
                        std::cout << "[ ]";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(1s);
    }

    move_thread.detach();
    fight_thread.detach();

    std::cout << "Game over! Surviving characters:" << std::endl;
    for (auto npc : array) {
        if (npc->is_alive()) { // Проверяем, кто выжил
            npc->print();
        }
    }

    return 0;
}
