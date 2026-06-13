#include "game/Game.hpp"
#include "game/AttributeRandomizer.hpp"
#include "game/WorldView.hpp"

namespace game {

Game::Game()
    : grid_(16, 12), party_(0, 1, 1) {

    AttributeRandomizer randomizer;

    auto addSlot = [&](PartySlot slot, Color color, const char* name) {
        PartyMember m{color, name, randomizer.generate()};
        m.setPartySlot(slot);
        party_.addMember(std::move(m));
    };

    addSlot(PartySlot::FrontLeft,  Color{0,   0,   255}, "Aragorn");
    addSlot(PartySlot::FrontRight, Color{255, 0,   0  }, "Legolas");
    addSlot(PartySlot::BackLeft,   Color{255, 255, 0  }, "Gimli");
    addSlot(PartySlot::BackRight,  Color{0,   255, 0  }, "Gandalf");

    grid_.place(party_.getId(), party_.getGridX(), party_.getGridY());

    auto enemy = std::make_unique<Enemy>(1, 14, 10, 2);
    grid_.place(enemy->getId(), enemy->getGridX(), enemy->getGridY());
    enemies_.push_back(std::move(enemy));
}

void Game::tick() {
    party_.snapshotPosition();
    for (auto& e : enemies_)
        e->snapshotPosition();

    WorldView view{grid_, party_};
    party_.think(view);
    for (auto& e : enemies_)
        e->think(view);

    party_.move(grid_, currentTick_);
    for (auto& e : enemies_)
        e->move(grid_, currentTick_);

    currentTick_++;
}

Party& Game::getParty() {
    return party_;
}

std::vector<GameObject*> Game::getAllObjects() {
    std::vector<GameObject*> objects;
    objects.reserve(1 + enemies_.size());
    objects.push_back(&party_);
    for (auto& e : enemies_)
        objects.push_back(e.get());
    return objects;
}

const Grid& Game::getGrid() const {
    return grid_;
}

} // namespace game
