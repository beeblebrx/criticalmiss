#pragma once

#include "Types.hpp"
#include <stdexcept>
#include <string>

namespace game {

enum class PartySlot { FrontLeft, FrontRight, BackLeft, BackRight };

struct Attributes {
    unsigned int health   = 0;
    unsigned int mana     = 0;
    unsigned int strength = 0;
    unsigned int agility  = 0;
    unsigned int wisdom   = 0;
};

class PartyMember {
public:
    static constexpr std::size_t MaxNameLength = 32;

    PartyMember(Color color, std::string name, Attributes attrs)
        : color_(color), attributes_(attrs) {
        if (name.size() > MaxNameLength)
            throw std::invalid_argument("PartyMember name exceeds maximum length of 32");
        name_ = std::move(name);
    }

    // Only call setPartySlot before handing the member to a Party.
    // To move a member between slots while in a party, use Party::swapMembers.
    void setPartySlot(PartySlot slot) { slot_ = slot; }
    PartySlot getSlot() const { return slot_; }

    Color getColor() const { return color_; }
    const std::string& getName() const { return name_; }
    const Attributes& getAttributes() const { return attributes_; }

private:
    PartySlot slot_ = PartySlot::FrontLeft;
    Color color_;
    std::string name_;
    Attributes attributes_;
};

} // namespace game
