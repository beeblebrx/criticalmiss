#include "game/Animate.hpp"

namespace game {

Animate::Animate(int id, int gridX, int gridY, Color color, int moveInterval)
    : GameObject(id, gridX, gridY, color), moveInterval_(moveInterval) {}

Direction Animate::getFacing() const { return facing_; }
void Animate::setFacing(Direction facing) { facing_ = facing; }

bool Animate::canMove(int currentTick) const {
    return currentTick - lastMoveTick_ >= moveInterval_;
}

} // namespace game
