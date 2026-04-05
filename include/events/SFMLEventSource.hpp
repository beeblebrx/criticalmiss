#pragma once

#include "events/IEventSource.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace events {

class SFMLEventSource : public IEventSource {
public:
    explicit SFMLEventSource(sf::RenderWindow& window);
    std::optional<sf::Event> pollEvent() override;

private:
    sf::RenderWindow& window_;
};

} // namespace events
