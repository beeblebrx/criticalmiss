#pragma once

#include "Creature.hpp"
#include "PartyMember.hpp"
#include "Types.hpp"
#include <map>
#include <vector>

namespace game {

class Party : public Creature {
public:
    Party(int id, int gridX, int gridY);

    void think(const WorldView& view) override;
    void move(Grid& grid, int currentTick) override;

    void bufferInput(Direction dir, bool strafe);
    void addMember(PartyMember member);

    const std::map<PartySlot, PartyMember>& getMembers() const;

    std::vector<const PartyMember*> frontRow() const;
    std::vector<const PartyMember*> backRow() const;
    std::vector<const PartyMember*> leftColumn() const;
    std::vector<const PartyMember*> rightColumn() const;

private:
    std::vector<const PartyMember*> slotsOf(PartySlot a, PartySlot b) const;

    std::map<PartySlot, PartyMember> members_;
    Direction bufferedDirection_ = Direction::None;
    bool bufferedStrafe_ = false;
};

} // namespace game
