#pragma once

#include "Grid.hpp"
#include "Types.hpp"

namespace game {

class GameObject {
public:
    GameObject(int id, int gridX, int gridY, Color color, int moveInterval);
    virtual ~GameObject() = default;

    virtual void onTick(Grid& grid, int currentTick) = 0;
    virtual void onCollision(GameObject& other) = 0;

    void moveTo(Grid& grid, int newX, int newY, int currentTick);
    void snapshotPosition();

    int getId() const;
    int getGridX() const;
    int getGridY() const;
    int getPrevGridX() const;
    int getPrevGridY() const;
    Color getColor() const;
    bool canMove(int currentTick) const;

protected:
    int id_;
    int gridX_, gridY_;
    int prevGridX_, prevGridY_;
    int moveInterval_;
    int lastMoveTick_ = -999;
    Color color_;
};

} // namespace game
