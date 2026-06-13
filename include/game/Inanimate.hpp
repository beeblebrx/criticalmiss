#pragma once

#include "GameObject.hpp"

namespace game {

class Inanimate : public GameObject {
protected:
    Inanimate(int id, int gridX, int gridY, Color color);
};

} // namespace game
