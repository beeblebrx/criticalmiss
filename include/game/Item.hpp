#pragma once

#include "Inanimate.hpp"

namespace game {

class Animate;

class Item : public Inanimate {
public:
    virtual void effect(Animate& user) = 0;

protected:
    Item(int id, int gridX, int gridY, Color color);
};

} // namespace game
