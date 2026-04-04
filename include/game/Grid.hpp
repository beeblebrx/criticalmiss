#pragma once

#include <SFML/System/Vector2.hpp>
#include <unordered_map>

class Grid {
public:
    Grid(int width, int height, float cellSize);

    bool isInBounds(int x, int y) const;
    bool isOccupied(int x, int y) const;
    void place(int id, int x, int y);
    void remove(int id, int x, int y);
    int getOccupant(int x, int y) const;

    sf::Vector2f cellToPixel(int x, int y) const;
    float getCellSize() const;
    int getWidth() const;
    int getHeight() const;

private:
    int key(int x, int y) const;

    int width_;
    int height_;
    float cellSize_;
    std::unordered_map<int, int> cells_;
};
