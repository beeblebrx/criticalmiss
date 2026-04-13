#include "game/Party.hpp"

namespace game {

Party::Party(int id, int gridX, int gridY)
    : GameObject(id, gridX, gridY, Color{255, 255, 255}, 1),
      members_{{
          {PartySlot::FrontLeft,  Color{0, 0, 255}},
          {PartySlot::FrontRight, Color{255, 0, 0}},
          {PartySlot::BackLeft,   Color{255, 255, 0}},
          {PartySlot::BackRight,  Color{0, 255, 0}}
      }} {}

void Party::onTick(Grid& grid, int currentTick) {
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
    // bufferedStrafe_ = false;

    int nx = gridX_ + dx, ny = gridY_ + dy;
    if (!grid.isInBounds(nx, ny))
        return;

    if (grid.isOccupied(nx, ny))
        return;

    if (!strafe)
        facing_ = moveDir;

    moveTo(grid, nx, ny, currentTick);
}

void Party::onCollision(GameObject& /*other*/) {}

void Party::bufferInput(Direction dir, bool strafe) {
    bufferedDirection_ = dir;
    bufferedStrafe_ = strafe;
}

Direction Party::getFacing() const {
    return facing_;
}

const std::array<PartyMember, 4>& Party::getMembers() const {
    return members_;
}

} // namespace game
