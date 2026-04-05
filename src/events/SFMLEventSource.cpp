#include "events/SFMLEventSource.hpp"

namespace events {

SFMLEventSource::SFMLEventSource(sf::RenderWindow& window)
    : window_(window) {}

std::optional<sf::Event> SFMLEventSource::pollEvent() {
    return window_.pollEvent();
}

} // namespace events
