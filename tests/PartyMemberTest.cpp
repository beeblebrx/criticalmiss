#include <gtest/gtest.h>
#include "game/PartyMember.hpp"
#include <stdexcept>

namespace {

TEST(PartyMemberTest, ConstructionStoresAllFields) {
    game::Attributes attrs{100, 50, 10, 8, 12};
    game::PartyMember member{game::Color{1, 2, 3}, "Aragorn", attrs};

    EXPECT_EQ(member.getColor().r, 1);
    EXPECT_EQ(member.getColor().g, 2);
    EXPECT_EQ(member.getColor().b, 3);
    EXPECT_EQ(member.getName(), "Aragorn");
    EXPECT_EQ(member.getAttributes().health,   100u);
    EXPECT_EQ(member.getAttributes().mana,      50u);
    EXPECT_EQ(member.getAttributes().strength,  10u);
    EXPECT_EQ(member.getAttributes().agility,    8u);
    EXPECT_EQ(member.getAttributes().wisdom,    12u);
}

TEST(PartyMemberTest, SetPartySlotRoundTrips) {
    game::PartyMember member{game::Color{}, "Test", game::Attributes{}};
    member.setPartySlot(game::PartySlot::BackRight);
    EXPECT_EQ(member.getSlot(), game::PartySlot::BackRight);
}

TEST(PartyMemberTest, EmptyNameIsAccepted) {
    EXPECT_NO_THROW((game::PartyMember{game::Color{}, "", game::Attributes{}}));
}

TEST(PartyMemberTest, NameAt32CharsIsAccepted) {
    EXPECT_NO_THROW((game::PartyMember{game::Color{}, std::string(32, 'x'), game::Attributes{}}));
}

TEST(PartyMemberTest, NameExceeding32CharsThrows) {
    EXPECT_THROW(
        (game::PartyMember{game::Color{}, std::string(33, 'x'), game::Attributes{}}),
        std::invalid_argument
    );
}

} // namespace
