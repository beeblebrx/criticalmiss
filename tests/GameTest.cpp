#include <gtest/gtest.h>
#include "game/Game.hpp"

namespace {

TEST(GameTest, PartyIsPlacedOnGridAtConstruction) {
    game::Game game;
    const auto& party = game.getParty();
    const auto& grid  = game.getGrid();

    EXPECT_TRUE(grid.isOccupied(party.getGridX(), party.getGridY()));
    EXPECT_EQ(grid.getOccupant(party.getGridX(), party.getGridY()), party.getId());
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
