#pragma once

#include <cstdint>

namespace game {

struct Color {
    uint8_t r, g, b, a = 255;
};

enum class Direction { None, Up, Down, Left, Right };

struct GameInput {
    Direction playerDirection = Direction::None;
    bool strafe = false;
    bool closeRequested = false;
};

} // namespace game
