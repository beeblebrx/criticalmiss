#pragma once

#include "events/IEventSource.hpp"
#include "game/Types.hpp"

namespace events {

class EventHandler {
public:
    explicit EventHandler(IEventSource& source);
    game::GameInput processEvents();

private:
    IEventSource& source_;
};

} // namespace events
