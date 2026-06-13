#include <gtest/gtest.h>
#include "game/SpikeTrap.hpp"
#include "TestCreature.hpp"

namespace {

using game_test::TestCreature;

TEST(TrapTest, SpikeTrapDamagesCreature) {
    game::SpikeTrap trap(1, 0, 0, 10);
    TestCreature creature(game::Attributes{50, 0, 0, 0, 0});

    trap.trigger(creature);

    EXPECT_EQ(creature.getAttributes().health, 40u);
}

TEST(TrapTest, SpikeTrapDoesNotUnderflowHealth) {
    game::SpikeTrap trap(1, 0, 0, 10);
    TestCreature creature(game::Attributes{5, 0, 0, 0, 0});

    trap.trigger(creature);

    EXPECT_EQ(creature.getAttributes().health, 0u);
    EXPECT_FALSE(creature.isAlive());
}

} // namespace
