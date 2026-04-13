#include <gtest/gtest.h>
#include "game/Party.hpp"
#include "game/Grid.hpp"

namespace {

class PartyTest : public ::testing::Test {
protected:
    game::Grid grid{16, 12};
    game::Party party{0, 3, 3};

    void SetUp() override {
        grid.place(party.getId(), party.getGridX(), party.getGridY());
    }
};

TEST_F(PartyTest, ConstructionSetsPosition) {
    EXPECT_EQ(party.getGridX(), 3);
    EXPECT_EQ(party.getGridY(), 3);
}

TEST_F(PartyTest, DefaultFacingIsUp) {
    EXPECT_EQ(party.getFacing(), game::Direction::Up);
}

TEST_F(PartyTest, HasFourMembers) {
    EXPECT_EQ(party.getMembers().size(), 4);
}

TEST_F(PartyTest, MembersHaveDistinctSlots) {
    const auto& members = party.getMembers();
    EXPECT_EQ(members[0].getSlot(), game::PartySlot::FrontLeft);
    EXPECT_EQ(members[1].getSlot(), game::PartySlot::FrontRight);
    EXPECT_EQ(members[2].getSlot(), game::PartySlot::BackLeft);
    EXPECT_EQ(members[3].getSlot(), game::PartySlot::BackRight);
}

TEST_F(PartyTest, NormalMoveChangesPositionAndFacing) {
    party.bufferInput(game::Direction::Right, false);
    party.onTick(grid, 0);

    EXPECT_EQ(party.getGridX(), 4);
    EXPECT_EQ(party.getGridY(), 3);
    EXPECT_EQ(party.getFacing(), game::Direction::Right);
}

TEST_F(PartyTest, StrafeMoveChangesPositionButNotFacing) {
    party.bufferInput(game::Direction::Right, true);
    party.onTick(grid, 0);

    EXPECT_EQ(party.getGridX(), 4);
    EXPECT_EQ(party.getGridY(), 3);
    EXPECT_EQ(party.getFacing(), game::Direction::Up);
}

TEST_F(PartyTest, MovementBlockedByBounds) {
    game::Grid smallGrid(4, 4);
    game::Party edgeParty(10, 0, 0);
    smallGrid.place(edgeParty.getId(), 0, 0);

    edgeParty.bufferInput(game::Direction::Left, false);
    edgeParty.onTick(smallGrid, 0);

    EXPECT_EQ(edgeParty.getGridX(), 0);
    EXPECT_EQ(edgeParty.getGridY(), 0);
}

TEST_F(PartyTest, MovementBlockedByOccupiedCell) {
    grid.place(99, 4, 3); // block the cell to the right

    party.bufferInput(game::Direction::Right, false);
    party.onTick(grid, 0);

    EXPECT_EQ(party.getGridX(), 3);
    EXPECT_EQ(party.getGridY(), 3);
}

TEST_F(PartyTest, FacingNotChangedWhenMovementBlocked) {
    grid.place(99, 4, 3);

    party.bufferInput(game::Direction::Right, false);
    party.onTick(grid, 0);

    EXPECT_EQ(party.getFacing(), game::Direction::Up);
}

TEST_F(PartyTest, NoInputNoMovement) {
    party.onTick(grid, 0);

    EXPECT_EQ(party.getGridX(), 3);
    EXPECT_EQ(party.getGridY(), 3);
}

TEST_F(PartyTest, SequentialMovesUpdateFacing) {
    party.bufferInput(game::Direction::Down, false);
    party.onTick(grid, 0);
    EXPECT_EQ(party.getFacing(), game::Direction::Down);

    party.bufferInput(game::Direction::Left, false);
    party.onTick(grid, 1);
    EXPECT_EQ(party.getFacing(), game::Direction::Left);
}

TEST_F(PartyTest, StrafeAfterFacingChangePreservesFacing) {
    party.bufferInput(game::Direction::Right, false);
    party.onTick(grid, 0);
    EXPECT_EQ(party.getFacing(), game::Direction::Right);

    party.bufferInput(game::Direction::Down, true);
    party.onTick(grid, 1);
    EXPECT_EQ(party.getFacing(), game::Direction::Right);
    EXPECT_EQ(party.getGridY(), 4);
}

} // namespace
