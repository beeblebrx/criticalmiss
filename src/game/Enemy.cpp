#include "game/Enemy.hpp"
#include "game/Level.hpp"
#include "game/Party.hpp"
#include "game/WorldView.hpp"
#include <cstdlib>

namespace game {

Enemy::Enemy(int id, int gridX, int gridY, int moveInterval)
    : Creature(id, gridX, gridY, Color{255, 0, 0}, moveInterval, Attributes{10, 0, 5, 5, 5}) {}

void Enemy::think(const WorldView& view) {
    targetX_ = view.party.getGridX();
    targetY_ = view.party.getGridY();
}

void Enemy::move(Level& level, int currentTick) {
    if (!canMove(currentTick))
        return;

    int dx = targetX_ - gridX_;
    int dy = targetY_ - gridY_;

    int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    struct Move { int x, y; };
    Move attempts[2];
    int count = 0;

    if (std::abs(dx) >= std::abs(dy)) {
        if (stepX != 0) attempts[count++] = {gridX_ + stepX, gridY_};
        if (stepY != 0) attempts[count++] = {gridX_, gridY_ + stepY};
    } else {
        if (stepY != 0) attempts[count++] = {gridX_, gridY_ + stepY};
        if (stepX != 0) attempts[count++] = {gridX_ + stepX, gridY_};
    }

    for (int i = 0; i < count; i++) {
        int nx = attempts[i].x, ny = attempts[i].y;
        if (level.isPassable(nx, ny) && !level.grid().isOccupied(nx, ny)) {
            if (nx > gridX_)      facing_ = Direction::Right;
            else if (nx < gridX_) facing_ = Direction::Left;
            else if (ny > gridY_) facing_ = Direction::Down;
            else if (ny < gridY_) facing_ = Direction::Up;

            moveTo(level.grid(), nx, ny);
            lastMoveTick_ = currentTick;
            return;
        }
    }
}

} // namespace game
