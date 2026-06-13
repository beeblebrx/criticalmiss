#include "game/Party.hpp"
#include "game/WorldView.hpp"
#include <stdexcept>

namespace game {

Party::Party(int id, int gridX, int gridY)
    : Creature(id, gridX, gridY, Color{255, 255, 255}, 1, Attributes{}) {}

void Party::addMember(PartyMember member) {
    PartySlot slot = member.getSlot();
    if (members_.count(slot))
        throw std::invalid_argument("Party already has a member in that slot");
    members_.emplace(slot, std::move(member));
}

void Party::think(const WorldView& /*view*/) {
    // Player-controlled: the next goal comes from bufferInput().
}

void Party::move(Grid& grid, int currentTick) {
    if (bufferedDirection_ == Direction::None || !canMove(currentTick))
        return;

    int dx = 0, dy = 0;
    switch (bufferedDirection_) {
        case Direction::Up:    dy = -1; break;
        case Direction::Down:  dy =  1; break;
        case Direction::Left:  dx = -1; break;
        case Direction::Right: dx =  1; break;
        default: break;
    }

    Direction moveDir = bufferedDirection_;
    bool strafe = bufferedStrafe_;
    bufferedDirection_ = Direction::None;

    int nx = gridX_ + dx, ny = gridY_ + dy;
    if (!grid.isInBounds(nx, ny))
        return;

    if (grid.isOccupied(nx, ny))
        return;

    if (!strafe)
        facing_ = moveDir;

    moveTo(grid, nx, ny);
    lastMoveTick_ = currentTick;
}

void Party::bufferInput(Direction dir, bool strafe) {
    bufferedDirection_ = dir;
    bufferedStrafe_ = strafe;
}

const std::map<PartySlot, PartyMember>& Party::getMembers() const {
    return members_;
}

std::vector<const PartyMember*> Party::frontRow() const {
    return slotsOf(PartySlot::FrontLeft, PartySlot::FrontRight);
}

std::vector<const PartyMember*> Party::backRow() const {
    return slotsOf(PartySlot::BackLeft, PartySlot::BackRight);
}

std::vector<const PartyMember*> Party::leftColumn() const {
    return slotsOf(PartySlot::FrontLeft, PartySlot::BackLeft);
}

std::vector<const PartyMember*> Party::rightColumn() const {
    return slotsOf(PartySlot::FrontRight, PartySlot::BackRight);
}

std::vector<const PartyMember*> Party::slotsOf(PartySlot a, PartySlot b) const {
    std::vector<const PartyMember*> result;
    for (PartySlot s : {a, b}) {
        auto it = members_.find(s);
        if (it != members_.end())
            result.push_back(&it->second);
    }
    return result;
}

} // namespace game
