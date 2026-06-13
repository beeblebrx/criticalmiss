#include "game/HealthPotion.hpp"
#include "game/Creature.hpp"

namespace game {

HealthPotion::HealthPotion(int id, int gridX, int gridY, unsigned int healAmount)
    : Item(id, gridX, gridY, Color{255, 0, 255}), healAmount_(healAmount) {}

void HealthPotion::effect(Animate& user) {
    auto* creature = dynamic_cast<Creature*>(&user);
    if (!creature)
        return;

    Attributes attrs = creature->getAttributes();
    attrs.health += healAmount_;
    creature->setAttributes(attrs);
}

} // namespace game
