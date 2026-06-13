#pragma once

#include "Item.hpp"

namespace game {

class HealthPotion : public Item {
public:
    HealthPotion(int id, int gridX, int gridY, unsigned int healAmount);

    void effect(Animate& user) override;

private:
    unsigned int healAmount_;
};

} // namespace game
