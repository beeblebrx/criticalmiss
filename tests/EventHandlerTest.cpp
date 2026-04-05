#include <gtest/gtest.h>
#include "events/EventHandler.hpp"
#include "events/IEventSource.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <queue>

namespace {

class FakeEventSource : public events::IEventSource {
public:
    void push(sf::Event event) { queue_.push(event); }

    std::optional<sf::Event> pollEvent() override {
        if (queue_.empty())
            return std::nullopt;
        sf::Event e = queue_.front();
        queue_.pop();
        return e;
    }

private:
    std::queue<sf::Event> queue_;
};

TEST(EventHandlerTest, NoEventsReturnsDefaultInput) {
    FakeEventSource source;
    events::EventHandler handler(source);

    auto input = handler.processEvents();

    EXPECT_EQ(input.playerDirection, game::Direction::None);
    EXPECT_FALSE(input.closeRequested);
}

TEST(EventHandlerTest, ClosedEventSetsCloseRequested) {
    FakeEventSource source;
    source.push(sf::Event::Closed{});
    events::EventHandler handler(source);

    auto input = handler.processEvents();

    EXPECT_TRUE(input.closeRequested);
}

TEST(EventHandlerTest, EscapeKeySetsCloseRequested) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Escape});
    events::EventHandler handler(source);

    auto input = handler.processEvents();

    EXPECT_TRUE(input.closeRequested);
}

TEST(EventHandlerTest, WKeySetsDirectionUp) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::W});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Up);
}

TEST(EventHandlerTest, UpArrowSetsDirectionUp) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Up});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Up);
}

TEST(EventHandlerTest, SKeySetDirectionDown) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::S});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Down);
}

TEST(EventHandlerTest, DownArrowSetsDirectionDown) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Down});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Down);
}

TEST(EventHandlerTest, AKeySetDirectionLeft) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::A});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Left);
}

TEST(EventHandlerTest, LeftArrowSetsDirectionLeft) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Left});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Left);
}

TEST(EventHandlerTest, DKeySetDirectionRight) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::D});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Right);
}

TEST(EventHandlerTest, RightArrowSetsDirectionRight) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Right});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Right);
}

TEST(EventHandlerTest, LastDirectionKeyWins) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::W});
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::S});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::Down);
}

TEST(EventHandlerTest, UnrelatedKeyLeavesDirectionNone) {
    FakeEventSource source;
    source.push(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Space});
    events::EventHandler handler(source);

    EXPECT_EQ(handler.processEvents().playerDirection, game::Direction::None);
}

} // namespace
