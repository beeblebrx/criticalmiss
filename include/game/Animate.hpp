#pragma once

#include "GameObject.hpp"
#include "Types.hpp"

namespace game {

struct WorldView;
class Level;

class Animate : public GameObject {
public:
    virtual void think(const WorldView& view) = 0;
    virtual void move(Level& level, int currentTick) = 0;

    Direction getFacing() const;
    void setFacing(Direction facing);

protected:
    Animate(int id, int gridX, int gridY, Color color, int moveInterval);

    bool canMove(int currentTick) const;

    Direction facing_ = Direction::Up;
    int moveInterval_;
    int lastMoveTick_ = -999;
};

} // namespace game
