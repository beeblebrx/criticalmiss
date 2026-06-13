#pragma once

#include "Grid.hpp"
#include "Types.hpp"

namespace game {

class GameObject {
public:
    virtual ~GameObject() = default;

    void moveTo(Grid& grid, int newX, int newY);
    void snapshotPosition();

    int getId() const;
    int getGridX() const;
    int getGridY() const;
    int getPrevGridX() const;
    int getPrevGridY() const;
    Color getColor() const;

protected:
    GameObject(int id, int gridX, int gridY, Color color);

    int id_;
    int gridX_, gridY_;
    int prevGridX_, prevGridY_;
    Color color_;
};

} // namespace game
