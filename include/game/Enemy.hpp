#pragma once

#include "GameObject.hpp"

namespace game {

class Enemy : public GameObject {
public:
    Enemy(int id, int gridX, int gridY, int moveInterval);

    void onTick(Grid& grid, int currentTick) override;
    void onCollision(GameObject& other) override;

    void setTarget(int targetX, int targetY);

private:
    int targetX_ = 0;
    int targetY_ = 0;
};

} // namespace game
