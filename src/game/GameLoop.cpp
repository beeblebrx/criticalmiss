#include "game/GameLoop.hpp"

namespace game {

GameLoop::GameLoop(float tickRate)
    : tickDuration_(1.0f / tickRate),
      maxAccumulator_(3.0f * tickDuration_) {}

void GameLoop::run(const Callbacks& cb) {
    float accumulator = 0.f;

    while (true) {
        float dt = cb.getElapsedTime();
        accumulator += dt;
        if (accumulator > maxAccumulator_)
            accumulator = maxAccumulator_;

        if (!cb.processInput())
            break;

        while (accumulator >= tickDuration_) {
            cb.tick();
            accumulator -= tickDuration_;
        }

        float alpha = accumulator / tickDuration_;
        cb.render(alpha);
    }
}

} // namespace game
