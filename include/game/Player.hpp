#pragma once

#include "GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

class Player : public GameObject {
public:
    Player(int id, int gridX, int gridY);

    void onTick(Grid& grid, int currentTick) override;
    void onCollision(GameObject& other) override;

    void bufferInput(sf::Keyboard::Key key);

private:
    sf::Keyboard::Key bufferedDirection_ = sf::Keyboard::Unknown;
};
