#include <gtest/gtest.h>
#include "game/Enemy.hpp"
#include "game/Party.hpp"
#include "game/Level.hpp"
#include "game/Tile.hpp"
#include "game/WorldView.hpp"

namespace {

TEST(EnemyTest, MovesCloserToPartyAfterThink) {
    game::Level level(16, 12);
    game::Party party(0, 5, 5);
    game::Enemy enemy(1, 10, 5, 1);
    level.grid().place(party.getId(), 5, 5);
    level.grid().place(enemy.getId(), 10, 5);

    game::WorldView view{level, party};
    enemy.think(view);
    enemy.move(level, 0);

    EXPECT_EQ(enemy.getGridX(), 9);
    EXPECT_EQ(enemy.getGridY(), 5);
}

TEST(EnemyTest, UpdatesFacingTowardMovement) {
    game::Level level(16, 12);
    game::Party party(0, 5, 5);
    game::Enemy enemy(1, 10, 5, 1);
    level.grid().place(party.getId(), 5, 5);
    level.grid().place(enemy.getId(), 10, 5);

    game::WorldView view{level, party};
    enemy.think(view);
    enemy.move(level, 0);

    EXPECT_EQ(enemy.getFacing(), game::Direction::Left);
}

TEST(EnemyTest, BlockedByWall) {
    game::Level level(16, 12);
    game::Party party(0, 5, 5);
    game::Enemy enemy(1, 10, 5, 1);
    level.grid().place(party.getId(), 5, 5);
    level.grid().place(enemy.getId(), 10, 5);
    level.setTile(9, 5, game::makeTile(game::TileType::RockWall));

    game::WorldView view{level, party};
    enemy.think(view);
    enemy.move(level, 0);

    EXPECT_EQ(enemy.getGridX(), 10);
    EXPECT_EQ(enemy.getGridY(), 5);
}

TEST(EnemyTest, BlockedByOccupiedCell) {
    game::Level level(16, 12);
    game::Party party(0, 5, 5);
    game::Enemy enemy(1, 10, 5, 1);
    level.grid().place(party.getId(), 5, 5);
    level.grid().place(enemy.getId(), 10, 5);
    level.grid().place(99, 9, 5);

    game::WorldView view{level, party};
    enemy.think(view);
    enemy.move(level, 0);

    EXPECT_EQ(enemy.getGridX(), 10);
    EXPECT_EQ(enemy.getGridY(), 5);
}

} // namespace
