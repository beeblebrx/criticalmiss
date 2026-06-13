#pragma once

namespace game {

class Grid;
class Party;

struct WorldView {
    const Grid& grid;
    const Party& party;
};

} // namespace game
