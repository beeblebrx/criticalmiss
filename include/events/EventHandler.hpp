#pragma once

#include "game/Types.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace events {

class EventHandler {
public:
    EventHandler(sf::RenderWindow& window);
    game::GameInput processEvents();

private:
    sf::RenderWindow& window_;
};

} // namespace events
