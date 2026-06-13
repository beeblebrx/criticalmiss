#include <gtest/gtest.h>
#include "game/Level.hpp"
#include "game/HealthPotion.hpp"
#include "game/SpikeTrap.hpp"
#include <memory>

namespace {

TEST(LevelTest, DefaultLevelIsAllFloorAndPassable) {
    game::Level level(5, 4);
    EXPECT_EQ(level.getWidth(), 5);
    EXPECT_EQ(level.getHeight(), 4);

    for (int y = 0; y < level.getHeight(); ++y)
        for (int x = 0; x < level.getWidth(); ++x)
            EXPECT_TRUE(level.isPassable(x, y));
}

TEST(LevelTest, WallTileIsNotPassable) {
    game::Level level(5, 4);
    level.setTile(2, 1, game::makeTile(game::TileType::RockWall));

    EXPECT_FALSE(level.isPassable(2, 1));
    EXPECT_FALSE(level.tileAt(2, 1).passable);
    EXPECT_TRUE(level.isPassable(1, 1));
}

TEST(LevelTest, OutOfBoundsIsNotPassable) {
    game::Level level(5, 4);
    EXPECT_FALSE(level.isPassable(-1, 0));
    EXPECT_FALSE(level.isPassable(0, -1));
    EXPECT_FALSE(level.isPassable(5, 0));
    EXPECT_FALSE(level.isPassable(0, 4));
}

TEST(LevelTest, MetadataRoundTrips) {
    game::Level level(5, 4);
    level.setName("Crypt");
    level.setMonsterCount(7);
    level.setTrapCount(3);
    level.setMaxItems(5);

    EXPECT_EQ(level.getName(), "Crypt");
    EXPECT_EQ(level.getMonsterCount(), 7);
    EXPECT_EQ(level.getTrapCount(), 3);
    EXPECT_EQ(level.getMaxItems(), 5);
}

TEST(LevelTest, LinksRoundTrip) {
    game::Level level(5, 4);
    level.setUpLevel("level0");
    level.setDownLevel("level2");

    EXPECT_EQ(level.getUpLevel(), "level0");
    EXPECT_EQ(level.getDownLevel(), "level2");
}

TEST(LevelTest, HoldsItemsAndTraps) {
    game::Level level(5, 4);
    level.addItem(std::make_unique<game::HealthPotion>(1, 1, 1, 10));
    level.addTrap(std::make_unique<game::SpikeTrap>(2, 2, 2, 5));

    EXPECT_EQ(level.items().size(), 1u);
    EXPECT_EQ(level.traps().size(), 1u);
}

TEST(LevelTest, TakeItemsAtRemovesOnlyMatchingCell) {
    game::Level level(5, 4);
    level.addItem(std::make_unique<game::HealthPotion>(1, 1, 1, 10));
    level.addItem(std::make_unique<game::HealthPotion>(2, 3, 2, 10));

    auto taken = level.takeItemsAt(1, 1);

    EXPECT_EQ(taken.size(), 1u);
    EXPECT_EQ(level.items().size(), 1u);
    EXPECT_EQ(level.items().front()->getGridX(), 3);
}

TEST(LevelTest, TakeItemsAtEmptyCellReturnsNothing) {
    game::Level level(5, 4);
    level.addItem(std::make_unique<game::HealthPotion>(1, 1, 1, 10));

    auto taken = level.takeItemsAt(4, 3);

    EXPECT_TRUE(taken.empty());
    EXPECT_EQ(level.items().size(), 1u);
}

} // namespace
