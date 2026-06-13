#include "game/SpikeTrap.hpp"
#include "game/Creature.hpp"

namespace game {

SpikeTrap::SpikeTrap(int id, int gridX, int gridY, unsigned int damage)
    : Trap(id, gridX, gridY, Color{128, 128, 128}), damage_(damage) {}

void SpikeTrap::trigger(Animate& victim) {
    auto* creature = dynamic_cast<Creature*>(&victim);
    if (!creature)
        return;

    Attributes attrs = creature->getAttributes();
    attrs.health = (attrs.health > damage_) ? attrs.health - damage_ : 0;
    creature->setAttributes(attrs);
}

} // namespace game
