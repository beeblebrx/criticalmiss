#pragma once

#include "game/Creature.hpp"

namespace game_test {

class TestCreature : public game::Creature {
public:
    explicit TestCreature(game::Attributes attrs)
        : Creature(0, 0, 0, game::Color{}, 1, attrs) {}

    void think(const game::WorldView&) override {}
    void move(game::Grid&, int) override {}
};

} // namespace game_test
