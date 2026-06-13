#pragma once

#include "Inanimate.hpp"

namespace game {

class Animate;

class Trap : public Inanimate {
public:
    virtual void trigger(Animate& victim) = 0;

protected:
    Trap(int id, int gridX, int gridY, Color color);
};

} // namespace game
