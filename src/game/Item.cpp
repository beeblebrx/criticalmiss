#include "game/Item.hpp"

namespace game {

Item::Item(int id, int gridX, int gridY, Color color)
    : Inanimate(id, gridX, gridY, color) {}

} // namespace game
