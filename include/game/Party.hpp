#pragma once

#include "GameObject.hpp"
#include "PartyMember.hpp"
#include "Types.hpp"
#include <map>
#include <vector>

namespace game {

class Party : public GameObject {
public:
    Party(int id, int gridX, int gridY);

    void onTick(Grid& grid, int currentTick) override;
    void onCollision(GameObject& other) override;

    void bufferInput(Direction dir, bool strafe);
    void addMember(PartyMember member);

    Direction getFacing() const;
    const std::map<PartySlot, PartyMember>& getMembers() const;

    std::vector<const PartyMember*> frontRow() const;
    std::vector<const PartyMember*> backRow() const;
    std::vector<const PartyMember*> leftColumn() const;
    std::vector<const PartyMember*> rightColumn() const;

private:
    std::vector<const PartyMember*> slotsOf(PartySlot a, PartySlot b) const;

    std::map<PartySlot, PartyMember> members_;
    Direction facing_ = Direction::Up;
    Direction bufferedDirection_ = Direction::None;
    bool bufferedStrafe_ = false;
};

} // namespace game
