#pragma once

#include "game/GameObject.hpp"
#include "game/Party.hpp"
#include "game/Grid.hpp"
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
                const game::Grid& grid, float alpha);

private:
    void drawGrid(const game::Grid& grid);
    void drawObject(const game::GameObject& obj, const game::Grid& grid, float alpha);
    void drawParty(const game::Party& party, const game::Grid& grid, float alpha);
    sf::Vector2f cellToPixel(int x, int y) const;

    sf::RenderWindow& window_;
    float cellSize_;
};

} // namespace render
