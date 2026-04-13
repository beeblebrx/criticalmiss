#pragma once

#include "GameObject.hpp"
#include "PartyMember.hpp"
#include "Types.hpp"
#include <array>

namespace game {

class Party : public GameObject {
public:
    Party(int id, int gridX, int gridY);

    void onTick(Grid& grid, int currentTick) override;
    void onCollision(GameObject& other) override;

    void bufferInput(Direction dir, bool strafe);

    Direction getFacing() const;
    const std::array<PartyMember, 4>& getMembers() const;

private:
    std::array<PartyMember, 4> members_;
    Direction facing_ = Direction::Up;
    Direction bufferedDirection_ = Direction::None;
    bool bufferedStrafe_ = false;
};

} // namespace game
