#include "game/AttributeRandomizer.hpp"

namespace game {

AttributeRandomizer::AttributeRandomizer() : rng_(std::random_device{}()) {}

AttributeRandomizer::AttributeRandomizer(unsigned int seed) : rng_(seed) {}

Attributes AttributeRandomizer::generate() {
    auto roll = [&](unsigned int lo, unsigned int hi) -> unsigned int {
        return std::uniform_int_distribution<unsigned int>{lo, hi}(rng_);
    };
    return Attributes{
        .health   = roll(50, 100),
        .mana     = roll(20,  60),
        .strength = roll( 5,  15),
        .agility  = roll( 5,  15),
        .wisdom   = roll( 5,  15),
    };
}

} // namespace game
