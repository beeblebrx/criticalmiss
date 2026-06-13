#include "game/World.hpp"

namespace game {

void World::addLevel(Level level) {
    levels_.push_back(std::move(level));
}

Level& World::currentLevel() { return levels_.at(current_); }
const Level& World::currentLevel() const { return levels_.at(current_); }

std::size_t World::levelCount() const { return levels_.size(); }

bool World::descend() {
    return moveTo(currentLevel().getDownLevel());
}

bool World::ascend() {
    return moveTo(currentLevel().getUpLevel());
}

bool World::moveTo(const std::string& name) {
    if (name.empty())
        return false;

    for (std::size_t i = 0; i < levels_.size(); ++i) {
        if (levels_[i].getName() == name) {
            current_ = i;
            return true;
        }
    }
    return false;
}

} // namespace game
