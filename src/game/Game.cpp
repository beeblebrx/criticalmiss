#include "game/Game.hpp"
#include "game/AttributeRandomizer.hpp"

namespace game {

Game::Game()
    : grid_(16, 12) {

    party_ = std::make_unique<Party>(0, 1, 1);

    AttributeRandomizer randomizer;

    auto addSlot = [&](PartySlot slot, Color color, const char* name) {
        PartyMember m{color, name, randomizer.generate()};
        m.setPartySlot(slot);
        party_->addMember(std::move(m));
    };

    addSlot(PartySlot::FrontLeft,  Color{0,   0,   255}, "Aragorn");
    addSlot(PartySlot::FrontRight, Color{255, 0,   0  }, "Legolas");
    addSlot(PartySlot::BackLeft,   Color{255, 255, 0  }, "Gimli");
    addSlot(PartySlot::BackRight,  Color{0,   255, 0  }, "Gandalf");

    grid_.place(party_->getId(), party_->getGridX(), party_->getGridY());

    auto enemy = std::make_unique<Enemy>(1, 14, 10, 2);
    grid_.place(enemy->getId(), enemy->getGridX(), enemy->getGridY());
    enemies_.push_back(std::move(enemy));

    allObjects_.push_back(party_.get());
    for (auto& e : enemies_)
        allObjects_.push_back(e.get());
}

void Game::tick() {
    for (auto* obj : allObjects_)
        obj->snapshotPosition();

    for (auto& enemy : enemies_)
        enemy->setTarget(party_->getGridX(), party_->getGridY());

    for (auto* obj : allObjects_)
        obj->onTick(grid_, currentTick_);

    currentTick_++;
}

Party& Game::getParty() {
    return *party_;
}

const std::vector<GameObject*>& Game::getAllObjects() const {
    return allObjects_;
}

const Grid& Game::getGrid() const {
    return grid_;
}

} // namespace game
