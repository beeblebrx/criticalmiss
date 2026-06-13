#include <gtest/gtest.h>
#include "game/Party.hpp"
#include "game/Grid.hpp"
#include <stdexcept>

namespace {

game::PartyMember makeMember(game::PartySlot slot) {
    game::PartyMember m{game::Color{0, 0, 0}, "Test", game::Attributes{}};
    m.setPartySlot(slot);
    return m;
}

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

TEST_F(PartyTest, NewPartyHasNoMembers) {
    EXPECT_TRUE(party.getMembers().empty());
}

TEST_F(PartyTest, AddMemberStoresBySlot) {
    party.addMember(makeMember(game::PartySlot::FrontLeft));
    EXPECT_EQ(party.getMembers().size(), 1u);
    EXPECT_NE(party.getMembers().find(game::PartySlot::FrontLeft), party.getMembers().end());
}

TEST_F(PartyTest, AddAllFourDistinctSlotsSucceeds) {
    party.addMember(makeMember(game::PartySlot::FrontLeft));
    party.addMember(makeMember(game::PartySlot::FrontRight));
    party.addMember(makeMember(game::PartySlot::BackLeft));
    party.addMember(makeMember(game::PartySlot::BackRight));
    EXPECT_EQ(party.getMembers().size(), 4u);
}

TEST_F(PartyTest, AddDuplicateSlotThrows) {
    party.addMember(makeMember(game::PartySlot::FrontLeft));
    EXPECT_THROW(party.addMember(makeMember(game::PartySlot::FrontLeft)), std::invalid_argument);
}

TEST_F(PartyTest, FrontRowReturnsFrontMembers) {
    party.addMember(makeMember(game::PartySlot::FrontLeft));
    party.addMember(makeMember(game::PartySlot::FrontRight));
    party.addMember(makeMember(game::PartySlot::BackLeft));
    auto row = party.frontRow();
    ASSERT_EQ(row.size(), 2u);
    EXPECT_EQ(row[0]->getSlot(), game::PartySlot::FrontLeft);
    EXPECT_EQ(row[1]->getSlot(), game::PartySlot::FrontRight);
}

TEST_F(PartyTest, BackRowReturnsBackMembers) {
    party.addMember(makeMember(game::PartySlot::BackLeft));
    party.addMember(makeMember(game::PartySlot::BackRight));
    auto row = party.backRow();
    ASSERT_EQ(row.size(), 2u);
    EXPECT_EQ(row[0]->getSlot(), game::PartySlot::BackLeft);
    EXPECT_EQ(row[1]->getSlot(), game::PartySlot::BackRight);
}

TEST_F(PartyTest, LeftColumnReturnsLeftMembers) {
    party.addMember(makeMember(game::PartySlot::FrontLeft));
    party.addMember(makeMember(game::PartySlot::BackLeft));
    auto col = party.leftColumn();
    ASSERT_EQ(col.size(), 2u);
    EXPECT_EQ(col[0]->getSlot(), game::PartySlot::FrontLeft);
    EXPECT_EQ(col[1]->getSlot(), game::PartySlot::BackLeft);
}

TEST_F(PartyTest, RightColumnReturnsRightMembers) {
    party.addMember(makeMember(game::PartySlot::FrontRight));
    party.addMember(makeMember(game::PartySlot::BackRight));
    auto col = party.rightColumn();
    ASSERT_EQ(col.size(), 2u);
    EXPECT_EQ(col[0]->getSlot(), game::PartySlot::FrontRight);
    EXPECT_EQ(col[1]->getSlot(), game::PartySlot::BackRight);
}

TEST_F(PartyTest, PartialRowReturnsOnlyOccupiedSlots) {
    party.addMember(makeMember(game::PartySlot::FrontLeft));
    EXPECT_EQ(party.frontRow().size(), 1u);
    EXPECT_EQ(party.backRow().size(), 0u);
}

TEST_F(PartyTest, NormalMoveChangesPositionAndFacing) {
    party.bufferInput(game::Direction::Right, false);
    party.move(grid, 0);

    EXPECT_EQ(party.getGridX(), 4);
    EXPECT_EQ(party.getGridY(), 3);
    EXPECT_EQ(party.getFacing(), game::Direction::Right);
}

TEST_F(PartyTest, StrafeMoveChangesPositionButNotFacing) {
    party.bufferInput(game::Direction::Right, true);
    party.move(grid, 0);

    EXPECT_EQ(party.getGridX(), 4);
    EXPECT_EQ(party.getGridY(), 3);
    EXPECT_EQ(party.getFacing(), game::Direction::Up);
}

TEST_F(PartyTest, MovementBlockedByBounds) {
    game::Grid smallGrid(4, 4);
    game::Party edgeParty(10, 0, 0);
    smallGrid.place(edgeParty.getId(), 0, 0);

    edgeParty.bufferInput(game::Direction::Left, false);
    edgeParty.move(smallGrid, 0);

    EXPECT_EQ(edgeParty.getGridX(), 0);
    EXPECT_EQ(edgeParty.getGridY(), 0);
}

TEST_F(PartyTest, MovementBlockedByOccupiedCell) {
    grid.place(99, 4, 3);

    party.bufferInput(game::Direction::Right, false);
    party.move(grid, 0);

    EXPECT_EQ(party.getGridX(), 3);
    EXPECT_EQ(party.getGridY(), 3);
}

TEST_F(PartyTest, FacingNotChangedWhenMovementBlocked) {
    grid.place(99, 4, 3);

    party.bufferInput(game::Direction::Right, false);
    party.move(grid, 0);

    EXPECT_EQ(party.getFacing(), game::Direction::Up);
}

TEST_F(PartyTest, NoInputNoMovement) {
    party.move(grid, 0);

    EXPECT_EQ(party.getGridX(), 3);
    EXPECT_EQ(party.getGridY(), 3);
}

TEST_F(PartyTest, SequentialMovesUpdateFacing) {
    party.bufferInput(game::Direction::Down, false);
    party.move(grid, 0);
    EXPECT_EQ(party.getFacing(), game::Direction::Down);

    party.bufferInput(game::Direction::Left, false);
    party.move(grid, 1);
    EXPECT_EQ(party.getFacing(), game::Direction::Left);
}

TEST_F(PartyTest, StrafeAfterFacingChangePreservesFacing) {
    party.bufferInput(game::Direction::Right, false);
    party.move(grid, 0);
    EXPECT_EQ(party.getFacing(), game::Direction::Right);

    party.bufferInput(game::Direction::Down, true);
    party.move(grid, 1);
    EXPECT_EQ(party.getFacing(), game::Direction::Right);
    EXPECT_EQ(party.getGridY(), 4);
}

} // namespace
