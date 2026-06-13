#include "game/Creature.hpp"

namespace game {

Creature::Creature(int id, int gridX, int gridY, Color color, int moveInterval, Attributes attrs)
    : Animate(id, gridX, gridY, color, moveInterval), attributes_(attrs) {}

const Attributes& Creature::getAttributes() const { return attributes_; }
void Creature::setAttributes(const Attributes& attrs) { attributes_ = attrs; }

bool Creature::isAlive() const { return attributes_.health > 0; }
void Creature::kill() { attributes_.health = 0; }

bool Creature::hasEffect(Effect effect) const {
    return effects_.test(static_cast<std::size_t>(effect));
}

void Creature::addEffect(Effect effect) {
    if (!isAlive())
        return;
    effects_.set(static_cast<std::size_t>(effect));
}

void Creature::removeEffect(Effect effect) {
    effects_.reset(static_cast<std::size_t>(effect));
}

} // namespace game
