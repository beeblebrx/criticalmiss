#include <gtest/gtest.h>
#include "game/HealthPotion.hpp"
#include "TestCreature.hpp"

namespace {

using game_test::TestCreature;

TEST(ItemTest, HealthPotionHealsCreature) {
    game::HealthPotion potion(1, 0, 0, 10);
    TestCreature creature(game::Attributes{50, 0, 0, 0, 0});

    potion.effect(creature);

    EXPECT_EQ(creature.getAttributes().health, 60u);
}

} // namespace
