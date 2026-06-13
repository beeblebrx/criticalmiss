#pragma once

#include "Grid.hpp"
#include "Tile.hpp"
#include "Item.hpp"
#include "Trap.hpp"
#include <memory>
#include <string>
#include <vector>

namespace game {

class Level {
public:
    Level(int width, int height);

    int getWidth() const;
    int getHeight() const;

    const Tile& tileAt(int x, int y) const;
    void setTile(int x, int y, Tile tile);
    bool isPassable(int x, int y) const;

    Grid& grid();
    const Grid& grid() const;

    const std::string& getName() const;
    void setName(std::string name);
    int getMonsterCount() const;
    void setMonsterCount(int count);
    int getTrapCount() const;
    void setTrapCount(int count);
    int getMaxItems() const;
    void setMaxItems(int count);

    const std::string& getUpLevel() const;
    void setUpLevel(std::string id);
    const std::string& getDownLevel() const;
    void setDownLevel(std::string id);

    void addItem(std::unique_ptr<Item> item);
    void addTrap(std::unique_ptr<Trap> trap);
    const std::vector<std::unique_ptr<Item>>& items() const;
    const std::vector<std::unique_ptr<Trap>>& traps() const;

    // Removes and returns all items at the given cell (item pickup).
    std::vector<std::unique_ptr<Item>> takeItemsAt(int x, int y);

private:
    int width_;
    int height_;
    Grid grid_;
    std::vector<Tile> tiles_;
    std::string name_;
    int monsterCount_ = 0;
    int trapCount_ = 0;
    int maxItems_ = 0;
    std::string upLevel_;
    std::string downLevel_;
    std::vector<std::unique_ptr<Item>> items_;
    std::vector<std::unique_ptr<Trap>> traps_;
};

} // namespace game
