#pragma once

#include "PartyMember.hpp"
#include <random>

namespace game {

class AttributeRandomizer {
public:
    AttributeRandomizer();
    explicit AttributeRandomizer(unsigned int seed);

    Attributes generate();

private:
    std::mt19937 rng_;
};

} // namespace game
