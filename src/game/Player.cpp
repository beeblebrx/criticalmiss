#include "game/Player.hpp"
#include <cstdio>

Player::Player(int id, int gridX, int gridY)
    : GameObject(id, gridX, gridY, sf::Color::Green, 1) {}

void Player::onTick(Grid& grid, int currentTick) {
    if (bufferedDirection_ == sf::Keyboard::Unknown || !canMove(currentTick))
        return;

    int dx = 0, dy = 0;
    switch (bufferedDirection_) {
        case sf::Keyboard::W: case sf::Keyboard::Up:    dy = -1; break;
        case sf::Keyboard::S: case sf::Keyboard::Down:  dy =  1; break;
        case sf::Keyboard::A: case sf::Keyboard::Left:  dx = -1; break;
        case sf::Keyboard::D: case sf::Keyboard::Right: dx =  1; break;
        default: break;
    }
    bufferedDirection_ = sf::Keyboard::Unknown;

    int nx = gridX_ + dx, ny = gridY_ + dy;
    if (!grid.isInBounds(nx, ny))
        return;

    if (grid.isOccupied(nx, ny))
        return;

    moveTo(grid, nx, ny, currentTick);
}

void Player::onCollision(GameObject& /*other*/) {
    moveInterval_++;
    std::printf("Player slowed! moveInterval = %d\n", moveInterval_);
}

void Player::bufferInput(sf::Keyboard::Key key) {
    bufferedDirection_ = key;
}
