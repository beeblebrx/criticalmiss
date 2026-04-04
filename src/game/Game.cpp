#include "game/Game.hpp"

namespace game {

Game::Game()
    : grid_(16, 12) {

    player_ = std::make_unique<Player>(0, 1, 1);
    grid_.place(player_->getId(), player_->getGridX(), player_->getGridY());

    auto enemy = std::make_unique<Enemy>(1, 14, 10, 2);
    grid_.place(enemy->getId(), enemy->getGridX(), enemy->getGridY());
    enemies_.push_back(std::move(enemy));

    allObjects_.push_back(player_.get());
    for (auto& e : enemies_)
        allObjects_.push_back(e.get());
}

void Game::tick() {
    for (auto* obj : allObjects_)
        obj->snapshotPosition();

    for (auto& enemy : enemies_)
        enemy->setTarget(player_->getGridX(), player_->getGridY());

    for (auto* obj : allObjects_)
        obj->onTick(grid_, currentTick_);

    currentTick_++;
}

Player& Game::getPlayer() {
    return *player_;
}

const std::vector<GameObject*>& Game::getAllObjects() const {
    return allObjects_;
}

const Grid& Game::getGrid() const {
    return grid_;
}

} // namespace game
