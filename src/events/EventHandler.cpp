#include "events/EventHandler.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace events {

EventHandler::EventHandler(sf::RenderWindow& window)
    : window_(window) {}

game::GameInput EventHandler::processEvents() {
    game::GameInput input;

    while (const std::optional<sf::Event> event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            input.closeRequested = true;
            continue;
        }

        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyEvent->code) {
                case sf::Keyboard::Key::W: case sf::Keyboard::Key::Up:
                    input.playerDirection = game::Direction::Up;
                    break;
                case sf::Keyboard::Key::S: case sf::Keyboard::Key::Down:
                    input.playerDirection = game::Direction::Down;
                    break;
                case sf::Keyboard::Key::A: case sf::Keyboard::Key::Left:
                    input.playerDirection = game::Direction::Left;
                    break;
                case sf::Keyboard::Key::D: case sf::Keyboard::Key::Right:
                    input.playerDirection = game::Direction::Right;
                    break;
                case sf::Keyboard::Key::Escape:
                    input.closeRequested = true;
                    break;
                default:
                    break;
            }
        }
    }

    return input;
}

} // namespace events
