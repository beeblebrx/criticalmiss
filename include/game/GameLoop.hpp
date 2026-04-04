#pragma once

#include <functional>

namespace game {

class GameLoop {
public:
    struct Callbacks {
        std::function<bool()> processInput;
        std::function<void()> tick;
        std::function<void(float)> render;
        std::function<float()> getElapsedTime;
    };

    GameLoop(float tickRate);
    void run(const Callbacks& cb);

private:
    float tickDuration_;
    float maxAccumulator_;
};

} // namespace game
