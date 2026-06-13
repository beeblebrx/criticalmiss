#pragma once

#include "Trap.hpp"

namespace game {

class SpikeTrap : public Trap {
public:
    SpikeTrap(int id, int gridX, int gridY, unsigned int damage);

    void trigger(Animate& victim) override;

private:
    unsigned int damage_;
};

} // namespace game
