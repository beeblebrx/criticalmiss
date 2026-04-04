#pragma once

#include <unordered_map>

namespace game {

class Grid {
public:
    Grid(int width, int height);

    bool isInBounds(int x, int y) const;
    bool isOccupied(int x, int y) const;
    void place(int id, int x, int y);
    void remove(int id, int x, int y);
    int getOccupant(int x, int y) const;

    int getWidth() const;
    int getHeight() const;

private:
    int key(int x, int y) const;

    int width_;
    int height_;
    std::unordered_map<int, int> cells_;
};

} // namespace game
