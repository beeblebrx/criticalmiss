#pragma once

#include "game/GameObject.hpp"
#include "game/Party.hpp"
#include "game/Level.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace render {

class Renderer {
public:
    Renderer(sf::RenderWindow& window, float cellSize);
    void render(const std::vector<game::GameObject*>& objects,
                const game::Level& level, float alpha);

private:
    void drawTiles(const game::Level& level);
    void drawGridLines(const game::Level& level);
    void drawObject(const game::GameObject& obj, float alpha);
    void drawParty(const game::Party& party, float alpha);
    sf::Vector2f cellToPixel(int x, int y) const;

    sf::RenderWindow& window_;
    float cellSize_;
};

} // namespace render
