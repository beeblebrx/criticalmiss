#include "game/GameObject.hpp"

namespace game {

GameObject::GameObject(int id, int gridX, int gridY, Color color)
    : id_(id), gridX_(gridX), gridY_(gridY),
      prevGridX_(gridX), prevGridY_(gridY), color_(color) {}

void GameObject::moveTo(Grid& grid, int newX, int newY) {
    grid.remove(id_, gridX_, gridY_);
    gridX_ = newX;
    gridY_ = newY;
    grid.place(id_, gridX_, gridY_);
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

} // namespace game
