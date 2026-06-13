#include "game/Game.hpp"
#include "game/GameLoop.hpp"
#include "game/World.hpp"
#include "render/Renderer.hpp"
#include "events/EventHandler.hpp"
#include "events/SFMLEventSource.hpp"
#include "io/LevelLoader.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include <utility>

int main() {
    constexpr float cellSize = 48.f;

    io::LevelLoader loader;
    game::World world;
    world.addLevel(loader.load(LEVEL1_PATH));

    const unsigned gridWidth  = static_cast<unsigned>(world.currentLevel().getWidth());
    const unsigned gridHeight = static_cast<unsigned>(world.currentLevel().getHeight());

    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned>(gridWidth * cellSize),
                       static_cast<unsigned>(gridHeight * cellSize)}),
        "Critical Miss");
    window.setVerticalSyncEnabled(true);

    game::Game game(std::move(world));
    render::Renderer renderer(window, cellSize);
    events::SFMLEventSource eventSource(window);
    events::EventHandler eventHandler(eventSource);
    sf::Clock clock;

    game::GameLoop loop(game::Game::TICK_RATE);
    loop.run({
        .processInput = [&]() {
            auto input = eventHandler.processEvents();
            if (input.closeRequested)
                window.close();
            if (input.playerDirection != game::Direction::None)
                game.getParty().bufferInput(input.playerDirection, input.strafe);
            return window.isOpen();
        },
        .tick = [&]() { game.tick(); },
        .render = [&](float alpha) {
            renderer.render(game.getAllObjects(), game.getCurrentLevel(), alpha);
        },
        .getElapsedTime = [&]() { return clock.restart().asSeconds(); }
    });

    return 0;
}
