#include "game/Enemy.hpp"
#include <cstdlib>
#include <cstdio>

Enemy::Enemy(int id, int gridX, int gridY, int moveInterval)
    : GameObject(id, gridX, gridY, sf::Color::Red, moveInterval) {}

void Enemy::onTick(Grid& grid, int currentTick) {
    if (!canMove(currentTick))
        return;

    int dx = targetX_ - gridX_;
    int dy = targetY_ - gridY_;

    // Pick primary axis (largest distance), fallback to other
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
        if (grid.isInBounds(nx, ny) && !grid.isOccupied(nx, ny)) {
            moveTo(grid, nx, ny, currentTick);
            return;
        }
    }
}

void Enemy::onCollision(GameObject& /*other*/) {
    std::printf("Enemy collided!\n");
}

void Enemy::setTarget(int targetX, int targetY) {
    targetX_ = targetX;
    targetY_ = targetY;
}
