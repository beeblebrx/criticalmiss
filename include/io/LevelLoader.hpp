#pragma once

#include "game/Level.hpp"
#include <string>

namespace io {

// Outer-layer adapter: reads a level file from disk and parses it into a Level.
// Throws std::runtime_error if the file cannot be opened.
class LevelLoader {
public:
    game::Level load(const std::string& path) const;
};

} // namespace io
