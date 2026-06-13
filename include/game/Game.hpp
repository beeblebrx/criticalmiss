#pragma once

#include "World.hpp"
#include "Party.hpp"
#include "Enemy.hpp"
#include <memory>
#include <vector>

namespace game {

class Game {
public:
    Game();
    explicit Game(World world);

    void tick();

    Party& getParty();
    std::vector<GameObject*> getAllObjects();
    const Grid& getGrid() const;
    const Level& getCurrentLevel() const;

    static constexpr float TICK_RATE = 3.0f;
    static constexpr float TICK_DURATION = 1.0f / TICK_RATE;
    static constexpr float MAX_ACCUMULATOR = 3.0f * TICK_DURATION;

private:
    void spawn();
    void resolveInteractions(Animate& animate);

    World world_;
    Party party_;
    std::vector<std::unique_ptr<Enemy>> enemies_;

    int currentTick_ = 0;
};

} // namespace game
