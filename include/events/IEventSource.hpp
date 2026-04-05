#pragma once

#include <optional>
#include <SFML/Window/Event.hpp>

namespace events {

class IEventSource {
public:
    virtual ~IEventSource() = default;
    virtual std::optional<sf::Event> pollEvent() = 0;
};

} // namespace events
