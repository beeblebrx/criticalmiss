#include "game/Player.hpp"
#include <cstdio>

namespace game {

Player::Player(int id, int gridX, int gridY)
    : GameObject(id, gridX, gridY, Color{0, 255, 0}, 1) {}

void Player::onTick(Grid& grid, int currentTick) {
    if (bufferedDirection_ == Direction::None || !canMove(currentTick))
        return;

    int dx = 0, dy = 0;
    switch (bufferedDirection_) {
        case Direction::Up:    dy = -1; break;
        case Direction::Down:  dy =  1; break;
        case Direction::Left:  dx = -1; break;
        case Direction::Right: dx =  1; break;
        default: break;
    }
    bufferedDirection_ = Direction::None;

    int nx = gridX_ + dx, ny = gridY_ + dy;
    if (!grid.isInBounds(nx, ny))
        return;

    if (grid.isOccupied(nx, ny))
        return;

    moveTo(grid, nx, ny, currentTick);
}

void Player::onCollision(GameObject& /*other*/) {
    moveInterval_++;
    std::printf("Player slowed! moveInterval = %d\n", moveInterval_);
}

void Player::bufferInput(Direction dir) {
    bufferedDirection_ = dir;
}

} // namespace game
