#include <gtest/gtest.h>
#include "game/Creature.hpp"
#include "TestCreature.hpp"

namespace {

using game_test::TestCreature;

TEST(CreatureTest, StoresAttributes) {
    game::Attributes attrs{100, 50, 10, 8, 12};
    TestCreature creature(attrs);

    EXPECT_EQ(creature.getAttributes().health,   100u);
    EXPECT_EQ(creature.getAttributes().mana,      50u);
    EXPECT_EQ(creature.getAttributes().strength,  10u);
    EXPECT_EQ(creature.getAttributes().agility,    8u);
    EXPECT_EQ(creature.getAttributes().wisdom,    12u);
}

TEST(CreatureTest, AliveWhenHealthPositive) {
    TestCreature creature(game::Attributes{10, 0, 0, 0, 0});
    EXPECT_TRUE(creature.isAlive());
}

TEST(CreatureTest, DeadWhenHealthIsZero) {
    TestCreature creature(game::Attributes{0, 0, 0, 0, 0});
    EXPECT_FALSE(creature.isAlive());
}

TEST(CreatureTest, KillSetsHealthToZeroAndMarksDead) {
    TestCreature creature(game::Attributes{10, 0, 0, 0, 0});
    creature.kill();

    EXPECT_FALSE(creature.isAlive());
    EXPECT_EQ(creature.getAttributes().health, 0u);
}

TEST(CreatureTest, NewCreatureHasNoEffects) {
    TestCreature creature(game::Attributes{10, 0, 0, 0, 0});
    EXPECT_FALSE(creature.hasEffect(game::Effect::Bleeding));
    EXPECT_FALSE(creature.hasEffect(game::Effect::Hungry));
    EXPECT_FALSE(creature.hasEffect(game::Effect::Confused));
    EXPECT_FALSE(creature.hasEffect(game::Effect::Blind));
    EXPECT_FALSE(creature.hasEffect(game::Effect::Unconscious));
}

TEST(CreatureTest, AddEffectSetsIt) {
    TestCreature creature(game::Attributes{10, 0, 0, 0, 0});
    creature.addEffect(game::Effect::Bleeding);
    EXPECT_TRUE(creature.hasEffect(game::Effect::Bleeding));
}

TEST(CreatureTest, RemoveEffectClearsIt) {
    TestCreature creature(game::Attributes{10, 0, 0, 0, 0});
    creature.addEffect(game::Effect::Confused);
    creature.removeEffect(game::Effect::Confused);
    EXPECT_FALSE(creature.hasEffect(game::Effect::Confused));
}

TEST(CreatureTest, EffectsCannotBeAddedWhenDead) {
    TestCreature creature(game::Attributes{0, 0, 0, 0, 0});
    creature.addEffect(game::Effect::Bleeding);
    EXPECT_FALSE(creature.hasEffect(game::Effect::Bleeding));
}

} // namespace
