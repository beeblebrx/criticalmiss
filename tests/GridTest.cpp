#include <gtest/gtest.h>
#include "game/Grid.hpp"

namespace {

// ── Construction ──────────────────────────────────────────────────────────────

TEST(GridTest, ReportsCorrectDimensions) {
    game::Grid grid(10, 8);
    EXPECT_EQ(grid.getWidth(),  10);
    EXPECT_EQ(grid.getHeight(),  8);
}

// ── isInBounds ────────────────────────────────────────────────────────────────

TEST(GridTest, OriginIsInBounds) {
    game::Grid grid(5, 5);
    EXPECT_TRUE(grid.isInBounds(0, 0));
}

TEST(GridTest, LastCellIsInBounds) {
    game::Grid grid(5, 5);
    EXPECT_TRUE(grid.isInBounds(4, 4));
}

TEST(GridTest, NegativeCoordinatesAreOutOfBounds) {
    game::Grid grid(5, 5);
    EXPECT_FALSE(grid.isInBounds(-1, 0));
    EXPECT_FALSE(grid.isInBounds(0, -1));
}

TEST(GridTest, CoordinatesAtWidthHeightAreOutOfBounds) {
    game::Grid grid(5, 5);
    EXPECT_FALSE(grid.isInBounds(5, 0));
    EXPECT_FALSE(grid.isInBounds(0, 5));
}

// ── place / isOccupied / getOccupant ─────────────────────────────────────────

TEST(GridTest, CellIsEmptyByDefault) {
    game::Grid grid(5, 5);
    EXPECT_FALSE(grid.isOccupied(2, 2));
    EXPECT_EQ(grid.getOccupant(2, 2), -1);
}

TEST(GridTest, PlacedObjectMarksCell) {
    game::Grid grid(5, 5);
    grid.place(42, 2, 3);
    EXPECT_TRUE(grid.isOccupied(2, 3));
    EXPECT_EQ(grid.getOccupant(2, 3), 42);
}

TEST(GridTest, PlaceDoesNotAffectOtherCells) {
    game::Grid grid(5, 5);
    grid.place(42, 2, 3);
    EXPECT_FALSE(grid.isOccupied(3, 2));
}

// ── remove ───────────────────────────────────────────────────────────────────

TEST(GridTest, RemoveClearsCell) {
    game::Grid grid(5, 5);
    grid.place(7, 1, 1);
    grid.remove(7, 1, 1);
    EXPECT_FALSE(grid.isOccupied(1, 1));
    EXPECT_EQ(grid.getOccupant(1, 1), -1);
}

TEST(GridTest, RemoveWithWrongIdDoesNotClearCell) {
    // Grid::remove only erases if the stored id matches.
    // This guards the invariant used in GameObject::moveTo.
    game::Grid grid(5, 5);
    grid.place(7, 1, 1);
    grid.remove(99, 1, 1);
    EXPECT_TRUE(grid.isOccupied(1, 1));
    EXPECT_EQ(grid.getOccupant(1, 1), 7);
}

TEST(GridTest, RemoveOnEmptyCellIsHarmless) {
    game::Grid grid(5, 5);
    EXPECT_NO_FATAL_FAILURE(grid.remove(1, 0, 0));
}

} // namespace
