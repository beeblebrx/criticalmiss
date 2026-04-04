#pragma once

#include "GameObject.hpp"
#include "Types.hpp"

namespace game {

class Player : public GameObject {
public:
    Player(int id, int gridX, int gridY);

    void onTick(Grid& grid, int currentTick) override;
    void onCollision(GameObject& other) override;

    void bufferInput(Direction dir);

private:
    Direction bufferedDirection_ = Direction::None;
};

} // namespace game
