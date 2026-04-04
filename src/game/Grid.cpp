#include "game/Grid.hpp"

namespace game {

Grid::Grid(int width, int height)
    : width_(width), height_(height) {}

bool Grid::isInBounds(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

bool Grid::isOccupied(int x, int y) const {
    return cells_.count(key(x, y)) > 0;
}

void Grid::place(int id, int x, int y) {
    cells_[key(x, y)] = id;
}

void Grid::remove(int id, int x, int y) {
    auto it = cells_.find(key(x, y));
    if (it != cells_.end() && it->second == id)
        cells_.erase(it);
}

int Grid::getOccupant(int x, int y) const {
    auto it = cells_.find(key(x, y));
    return (it != cells_.end()) ? it->second : -1;
}

int Grid::getWidth() const { return width_; }
int Grid::getHeight() const { return height_; }

int Grid::key(int x, int y) const {
    return y * width_ + x;
}

} // namespace game
