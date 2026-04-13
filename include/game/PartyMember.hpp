#pragma once

#include "Types.hpp"

namespace game {

enum class PartySlot { FrontLeft, FrontRight, BackLeft, BackRight };

class PartyMember {
public:
    PartyMember(PartySlot slot, Color color)
        : slot_(slot), color_(color) {}

    PartySlot getSlot() const { return slot_; }
    Color getColor() const { return color_; }

private:
    PartySlot slot_;
    Color color_;
};

} // namespace game
