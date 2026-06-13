#pragma once

#include "Types.hpp"

namespace game {

struct Tile {
    Color color;
    bool passable;
};

enum class TileType { RockFloor, RockWall };

inline Tile makeTile(TileType type) {
    switch (type) {
        case TileType::RockWall:  return Tile{Color{90, 90, 90}, false};
        case TileType::RockFloor: return Tile{Color{60, 45, 35}, true};
    }
    return Tile{Color{0, 0, 0}, false};
}

} // namespace game
