#include "game/GameObject.hpp"

GameObject::GameObject(int id, int gridX, int gridY, sf::Color color, int moveInterval)
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

void GameObject::render(sf::RenderWindow& window, const Grid& grid, float alpha) const {
    sf::Vector2f prev = grid.cellToPixel(prevGridX_, prevGridY_);
    sf::Vector2f curr = grid.cellToPixel(gridX_, gridY_);
    sf::Vector2f pos = prev + alpha * (curr - prev);

    float size = grid.getCellSize() - 2.f;
    sf::RectangleShape shape({size, size});
    shape.setPosition(pos.x + 1.f, pos.y + 1.f);
    shape.setFillColor(color_);
    window.draw(shape);
}

int GameObject::getId() const { return id_; }
int GameObject::getGridX() const { return gridX_; }
int GameObject::getGridY() const { return gridY_; }

bool GameObject::canMove(int currentTick) const {
    return currentTick - lastMoveTick_ >= moveInterval_;
}
