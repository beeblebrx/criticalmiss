#include "game/Game.hpp"
#include "game/GameLoop.hpp"
#include "render/Renderer.hpp"
#include "events/EventHandler.hpp"
#include "events/SFMLEventSource.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>

int main() {
    constexpr float cellSize = 48.f;
    constexpr int gridWidth = 16;
    constexpr int gridHeight = 12;

    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned>(gridWidth * cellSize),
                       static_cast<unsigned>(gridHeight * cellSize)}),
        "Critical Miss");
    window.setVerticalSyncEnabled(true);

    game::Game game;
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
            renderer.render(game.getAllObjects(), game.getGrid(), alpha);
        },
        .getElapsedTime = [&]() { return clock.restart().asSeconds(); }
    });

    return 0;
}
