#include <gtest/gtest.h>
#include "game/Game.hpp"

namespace {

TEST(GameTest, PlayerIsPlacedOnGridAtConstruction) {
    game::Game game;
    const auto& player = game.getPlayer();
    const auto& grid   = game.getGrid();

    EXPECT_TRUE(grid.isOccupied(player.getGridX(), player.getGridY()));
    EXPECT_EQ(grid.getOccupant(player.getGridX(), player.getGridY()), player.getId());
}

TEST(GameTest, AllObjectsListIsNonEmpty) {
    game::Game game;
    EXPECT_FALSE(game.getAllObjects().empty());
}

TEST(GameTest, TickDoesNotCrash) {
    game::Game game;
    EXPECT_NO_FATAL_FAILURE(game.tick());
}

} // namespace
