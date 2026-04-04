#include "game/GameObject.hpp"

namespace game {

GameObject::GameObject(int id, int gridX, int gridY, Color color, int moveInterval)
    : id_(id), gridX_(gridX), gridY_(gridY),
      prevGridX_(gridX), prevGridY_(gridY),
      moveInterval_(moveInterval), color_(color) {}

void GameObject::moveTo(Grid& grid, int newX, int newY, int currentTick) {
    grid.remove(id_, gridX_, gridY_);
    gridX_ = newX;
    gridY_ = newY;
    grid.place(id_, gridX_, gridY_);
    lastMoveTick_ = currentTick;
}

void GameObject::snapshotPosition() {
    prevGridX_ = gridX_;
    prevGridY_ = gridY_;
}

int GameObject::getId() const { return id_; }
int GameObject::getGridX() const { return gridX_; }
int GameObject::getGridY() const { return gridY_; }
int GameObject::getPrevGridX() const { return prevGridX_; }
int GameObject::getPrevGridY() const { return prevGridY_; }
Color GameObject::getColor() const { return color_; }

bool GameObject::canMove(int currentTick) const {
    return currentTick - lastMoveTick_ >= moveInterval_;
}

} // namespace game
