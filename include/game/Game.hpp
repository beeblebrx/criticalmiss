#pragma once

#include "Grid.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void tick();
    void render(float alpha);
    void drawGrid();

    sf::RenderWindow window_;
    Grid grid_;
    std::unique_ptr<Player> player_;
    std::vector<std::unique_ptr<Enemy>> enemies_;
    std::vector<GameObject*> allObjects_;

    int currentTick_ = 0;

    static constexpr float TICK_RATE = 3.0f;
    static constexpr float TICK_DURATION = 1.0f / TICK_RATE;
    static constexpr float MAX_ACCUMULATOR = 3.0f * TICK_DURATION;
};
