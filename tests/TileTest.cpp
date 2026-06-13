#include <gtest/gtest.h>
#include "game/Tile.hpp"

namespace {

TEST(TileTest, RockFloorIsPassable) {
    game::Tile tile = game::makeTile(game::TileType::RockFloor);
    EXPECT_TRUE(tile.passable);
}

TEST(TileTest, RockWallIsImpassable) {
    game::Tile tile = game::makeTile(game::TileType::RockWall);
    EXPECT_FALSE(tile.passable);
}

TEST(TileTest, FloorAndWallHaveDistinctColors) {
    game::Tile floor = game::makeTile(game::TileType::RockFloor);
    game::Tile wall  = game::makeTile(game::TileType::RockWall);

    bool sameColor = floor.color.r == wall.color.r &&
                     floor.color.g == wall.color.g &&
                     floor.color.b == wall.color.b;
    EXPECT_FALSE(sameColor);
}

} // namespace
