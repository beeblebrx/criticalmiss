#pragma once

#include "Level.hpp"
#include <cstddef>
#include <vector>

namespace game {

// Owns the linked collection of dungeon levels and tracks the current one.
// Levels are linked by name via each level's up/down identifiers.
class World {
public:
    void addLevel(Level level);

    Level& currentLevel();
    const Level& currentLevel() const;
    std::size_t levelCount() const;

    bool descend();
    bool ascend();

private:
    bool moveTo(const std::string& name);

    std::vector<Level> levels_;
    std::size_t current_ = 0;
};

} // namespace game
