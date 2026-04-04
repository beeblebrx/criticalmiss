#include "render/Renderer.hpp"

namespace render {

static sf::Color toSfColor(const game::Color& c) {
    return sf::Color(c.r, c.g, c.b, c.a);
}

Renderer::Renderer(sf::RenderWindow& window, float cellSize)
    : window_(window), cellSize_(cellSize) {}

void Renderer::render(const std::vector<game::GameObject*>& objects,
                      const game::Grid& grid, float alpha) {
    window_.clear(sf::Color(30, 30, 30));
    drawGrid(grid);

    for (auto* obj : objects)
        drawObject(*obj, grid, alpha);

    window_.display();
}

void Renderer::drawGrid(const game::Grid& grid) {
    float w = grid.getWidth() * cellSize_;
    float h = grid.getHeight() * cellSize_;
    sf::Color lineColor(60, 60, 60);

    for (int x = 0; x <= grid.getWidth(); x++) {
        sf::RectangleShape line({1.f, h});
        line.setPosition({x * cellSize_, 0.f});
        line.setFillColor(lineColor);
        window_.draw(line);
    }

    for (int y = 0; y <= grid.getHeight(); y++) {
        sf::RectangleShape line({w, 1.f});
        line.setPosition({0.f, y * cellSize_});
        line.setFillColor(lineColor);
        window_.draw(line);
    }
}

void Renderer::drawObject(const game::GameObject& obj, const game::Grid& grid, float alpha) {
    sf::Vector2f prev = cellToPixel(obj.getPrevGridX(), obj.getPrevGridY());
    sf::Vector2f curr = cellToPixel(obj.getGridX(), obj.getGridY());
    sf::Vector2f pos = prev + alpha * (curr - prev);

    float size = cellSize_ - 2.f;
    sf::RectangleShape shape({size, size});
    shape.setPosition({pos.x + 1.f, pos.y + 1.f});
    shape.setFillColor(toSfColor(obj.getColor()));
    window_.draw(shape);
}

sf::Vector2f Renderer::cellToPixel(int x, int y) const {
    return {static_cast<float>(x) * cellSize_, static_cast<float>(y) * cellSize_};
}

} // namespace render
