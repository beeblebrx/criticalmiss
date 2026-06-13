#pragma once

#include "Creature.hpp"

namespace game {

class Enemy : public Creature {
public:
    Enemy(int id, int gridX, int gridY, int moveInterval);

    void think(const WorldView& view) override;
    void move(Level& level, int currentTick) override;

private:
    int targetX_ = 0;
    int targetY_ = 0;
};

} // namespace game
