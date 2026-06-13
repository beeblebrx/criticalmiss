#include "game/Trap.hpp"

namespace game {

Trap::Trap(int id, int gridX, int gridY, Color color)
    : Inanimate(id, gridX, gridY, color) {}

} // namespace game
