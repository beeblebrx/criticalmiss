#pragma once

#include "Grid.hpp"
#include "Party.hpp"
#include "Enemy.hpp"
#include <memory>
#include <vector>

namespace game {

class Game {
public:
    Game();
    void tick();

    Party& getParty();
    const std::vector<GameObject*>& getAllObjects() const;
    const Grid& getGrid() const;

    static constexpr float TICK_RATE = 3.0f;
    static constexpr float TICK_DURATION = 1.0f / TICK_RATE;
    static constexpr float MAX_ACCUMULATOR = 3.0f * TICK_DURATION;

private:
    Grid grid_;
    std::unique_ptr<Party> party_;
    std::vector<std::unique_ptr<Enemy>> enemies_;
    std::vector<GameObject*> allObjects_;

    int currentTick_ = 0;
};

} // namespace game
