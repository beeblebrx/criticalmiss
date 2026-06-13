#pragma once

namespace game {

class Level;
class Party;

struct WorldView {
    const Level& level;
    const Party& party;
};

} // namespace game
