#include "game/Game.hpp"
#include "game/AttributeRandomizer.hpp"
#include "game/LevelParser.hpp"
#include "game/WorldView.hpp"

namespace game {

namespace {

// Fallback starting level for the default constructor (used by tests so they
// need no filesystem). The real app loads a level file via io::LevelLoader.
const char* const kStartLevel =
    "name: The Entrance\n"
    "monsters: 1\n"
    "traps: 0\n"
    "max_items: 3\n"
    "up: -\n"
    "down: -\n"
    "---\n"
    "################\n"
    "#..............#\n"
    "#..............#\n"
    "#..............#\n"
    "#..............#\n"
    "#..............#\n"
    "#..............#\n"
    "#..............#\n"
    "#..............#\n"
    "#..............#\n"
    "#..............#\n"
    "################\n";

World makeDefaultWorld() {
    LevelParser parser;
    World world;
    world.addLevel(parser.parse(kStartLevel));
    return world;
}

} // namespace

Game::Game()
    : Game(makeDefaultWorld()) {}

Game::Game(World world)
    : world_(std::move(world)), party_(0, 1, 1) {
    spawn();
}

void Game::spawn() {
    Level& level = world_.currentLevel();

    AttributeRandomizer randomizer;

    auto addSlot = [&](PartySlot slot, Color color, const char* name) {
        PartyMember m{color, name, randomizer.generate()};
        m.setPartySlot(slot);
        party_.addMember(std::move(m));
    };

    addSlot(PartySlot::FrontLeft,  Color{0,   0,   255}, "Aragorn");
    addSlot(PartySlot::FrontRight, Color{255, 0,   0  }, "Legolas");
    addSlot(PartySlot::BackLeft,   Color{255, 255, 0  }, "Gimli");
    addSlot(PartySlot::BackRight,  Color{0,   255, 0  }, "Gandalf");

    level.grid().place(party_.getId(), party_.getGridX(), party_.getGridY());

    auto enemy = std::make_unique<Enemy>(1, 14, 10, 2);
    level.grid().place(enemy->getId(), enemy->getGridX(), enemy->getGridY());
    enemies_.push_back(std::move(enemy));
}

void Game::tick() {
    Level& level = world_.currentLevel();

    party_.snapshotPosition();
    for (auto& e : enemies_)
        e->snapshotPosition();

    WorldView view{level, party_};
    party_.think(view);
    for (auto& e : enemies_)
        e->think(view);

    party_.move(level, currentTick_);
    for (auto& e : enemies_)
        e->move(level, currentTick_);

    resolveInteractions(party_);
    for (auto& e : enemies_)
        resolveInteractions(*e);

    currentTick_++;
}

void Game::resolveInteractions(Animate& animate) {
    bool enteredNewCell = animate.getGridX() != animate.getPrevGridX() ||
                          animate.getGridY() != animate.getPrevGridY();
    if (!enteredNewCell)
        return;

    Level& level = world_.currentLevel();
    int x = animate.getGridX();
    int y = animate.getGridY();

    for (auto& trap : level.traps())
        if (trap->getGridX() == x && trap->getGridY() == y)
            trap->trigger(animate);

    for (auto& item : level.takeItemsAt(x, y))
        item->effect(animate);
}

Party& Game::getParty() {
    return party_;
}

std::vector<GameObject*> Game::getAllObjects() {
    std::vector<GameObject*> objects;
    objects.reserve(1 + enemies_.size());
    objects.push_back(&party_);
    for (auto& e : enemies_)
        objects.push_back(e.get());
    return objects;
}

const Grid& Game::getGrid() const {
    return world_.currentLevel().grid();
}

const Level& Game::getCurrentLevel() const {
    return world_.currentLevel();
}

} // namespace game
