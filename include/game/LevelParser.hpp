#pragma once

#include "Level.hpp"
#include <string>

namespace game {

// Parses a level description (header + ASCII map) into a Level.
// Pure standard library: no filesystem access. Throws std::invalid_argument
// on malformed input.
class LevelParser {
public:
    Level parse(const std::string& text) const;
};

} // namespace game
