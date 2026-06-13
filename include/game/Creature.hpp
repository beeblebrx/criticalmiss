#pragma once

#include "Animate.hpp"
#include "Attributes.hpp"
#include <bitset>

namespace game {

enum class Effect { Bleeding, Hungry, Confused, Blind, Unconscious, MAX };

class Creature : public Animate {
public:
    const Attributes& getAttributes() const;
    void setAttributes(const Attributes& attrs);

    bool isAlive() const;
    void kill();

    bool hasEffect(Effect effect) const;
    void addEffect(Effect effect);
    void removeEffect(Effect effect);

protected:
    Creature(int id, int gridX, int gridY, Color color, int moveInterval, Attributes attrs);

private:
    Attributes attributes_;
    std::bitset<static_cast<std::size_t>(Effect::MAX)> effects_;
};

} // namespace game
