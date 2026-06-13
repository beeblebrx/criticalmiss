#include "game/Level.hpp"

namespace game {

Level::Level(int width, int height)
    : width_(width), height_(height), grid_(width, height),
      tiles_(static_cast<std::size_t>(width) * height, makeTile(TileType::RockFloor)) {}

int Level::getWidth() const { return width_; }
int Level::getHeight() const { return height_; }

const Tile& Level::tileAt(int x, int y) const {
    return tiles_[static_cast<std::size_t>(y) * width_ + x];
}

void Level::setTile(int x, int y, Tile tile) {
    tiles_[static_cast<std::size_t>(y) * width_ + x] = tile;
}

bool Level::isPassable(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_)
        return false;
    return tiles_[static_cast<std::size_t>(y) * width_ + x].passable;
}

Grid& Level::grid() { return grid_; }
const Grid& Level::grid() const { return grid_; }

const std::string& Level::getName() const { return name_; }
void Level::setName(std::string name) { name_ = std::move(name); }
int Level::getMonsterCount() const { return monsterCount_; }
void Level::setMonsterCount(int count) { monsterCount_ = count; }
int Level::getTrapCount() const { return trapCount_; }
void Level::setTrapCount(int count) { trapCount_ = count; }
int Level::getMaxItems() const { return maxItems_; }
void Level::setMaxItems(int count) { maxItems_ = count; }

const std::string& Level::getUpLevel() const { return upLevel_; }
void Level::setUpLevel(std::string id) { upLevel_ = std::move(id); }
const std::string& Level::getDownLevel() const { return downLevel_; }
void Level::setDownLevel(std::string id) { downLevel_ = std::move(id); }

void Level::addItem(std::unique_ptr<Item> item) { items_.push_back(std::move(item)); }
void Level::addTrap(std::unique_ptr<Trap> trap) { traps_.push_back(std::move(trap)); }
const std::vector<std::unique_ptr<Item>>& Level::items() const { return items_; }
const std::vector<std::unique_ptr<Trap>>& Level::traps() const { return traps_; }

std::vector<std::unique_ptr<Item>> Level::takeItemsAt(int x, int y) {
    std::vector<std::unique_ptr<Item>> taken;
    std::vector<std::unique_ptr<Item>> remaining;
    for (auto& item : items_) {
        if (item->getGridX() == x && item->getGridY() == y)
            taken.push_back(std::move(item));
        else
            remaining.push_back(std::move(item));
    }
    items_ = std::move(remaining);
    return taken;
}

} // namespace game
