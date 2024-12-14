#pragma once

#include <memory>
#include <istream>
#include <string>
#include "npc.h" // Заголовочный файл с объявлением NPC и типов NpcType

std::shared_ptr<NPC> factory(std::istream& is);
std::shared_ptr<NPC> factory(NpcType type, int x, int y);
