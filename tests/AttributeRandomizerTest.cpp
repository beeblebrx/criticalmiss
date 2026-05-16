#include <gtest/gtest.h>
#include "game/AttributeRandomizer.hpp"

namespace {

TEST(AttributeRandomizerTest, GeneratedAttributesAreInRange) {
    game::AttributeRandomizer randomizer{42};
    for (int i = 0; i < 20; ++i) {
        auto attrs = randomizer.generate();
        EXPECT_GE(attrs.health,    50u); EXPECT_LE(attrs.health,   100u);
        EXPECT_GE(attrs.mana,      20u); EXPECT_LE(attrs.mana,      60u);
        EXPECT_GE(attrs.strength,   5u); EXPECT_LE(attrs.strength,  15u);
        EXPECT_GE(attrs.agility,    5u); EXPECT_LE(attrs.agility,   15u);
        EXPECT_GE(attrs.wisdom,     5u); EXPECT_LE(attrs.wisdom,    15u);
    }
}

TEST(AttributeRandomizerTest, SameSeedProducesSameSequence) {
    game::AttributeRandomizer r1{99};
    game::AttributeRandomizer r2{99};

    for (int i = 0; i < 4; ++i) {
        auto a1 = r1.generate();
        auto a2 = r2.generate();
        EXPECT_EQ(a1.health,   a2.health);
        EXPECT_EQ(a1.mana,     a2.mana);
        EXPECT_EQ(a1.strength, a2.strength);
        EXPECT_EQ(a1.agility,  a2.agility);
        EXPECT_EQ(a1.wisdom,   a2.wisdom);
    }
}

TEST(AttributeRandomizerTest, GeneratedAttributesAreNonZero) {
    game::AttributeRandomizer randomizer{7};
    auto attrs = randomizer.generate();
    EXPECT_GT(attrs.health,   0u);
    EXPECT_GT(attrs.mana,     0u);
    EXPECT_GT(attrs.strength, 0u);
    EXPECT_GT(attrs.agility,  0u);
    EXPECT_GT(attrs.wisdom,   0u);
}

} // namespace
