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

    for (auto* obj : objects) {
        if (auto* party = dynamic_cast<const game::Party*>(obj))
            drawParty(*party, grid, alpha);
        else
            drawObject(*obj, grid, alpha);
    }

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

void Renderer::drawParty(const game::Party& party, const game::Grid& grid, float alpha) {
    sf::Vector2f prev = cellToPixel(party.getPrevGridX(), party.getPrevGridY());
    sf::Vector2f curr = cellToPixel(party.getGridX(), party.getGridY());
    sf::Vector2f pos = prev + alpha * (curr - prev);

    float halfSize = (cellSize_ - 2.f) / 2.f;
    float padding = 1.f;

    // Map each slot to a quadrant index (0=TopLeft, 1=TopRight, 2=BottomLeft, 3=BottomRight)
    // based on facing direction.
    // Quadrant offsets: 0=(0,0), 1=(half,0), 2=(0,half), 3=(half,half)
    int slotToQuad[4]; // indexed by PartySlot enum

    switch (party.getFacing()) {
        case game::Direction::Up:
            slotToQuad[0] = 0; // FrontLeft  -> TopLeft
            slotToQuad[1] = 1; // FrontRight -> TopRight
            slotToQuad[2] = 2; // BackLeft   -> BottomLeft
            slotToQuad[3] = 3; // BackRight  -> BottomRight
            break;
        case game::Direction::Down:
            slotToQuad[0] = 3; // FrontLeft  -> BottomRight
            slotToQuad[1] = 2; // FrontRight -> BottomLeft
            slotToQuad[2] = 1; // BackLeft   -> TopRight
            slotToQuad[3] = 0; // BackRight  -> TopLeft
            break;
        case game::Direction::Right:
            slotToQuad[0] = 1; // FrontLeft  -> TopRight
            slotToQuad[1] = 3; // FrontRight -> BottomRight
            slotToQuad[2] = 0; // BackLeft   -> TopLeft
            slotToQuad[3] = 2; // BackRight  -> BottomLeft
            break;
        case game::Direction::Left:
            slotToQuad[0] = 2; // FrontLeft  -> BottomLeft
            slotToQuad[1] = 0; // FrontRight -> TopLeft
            slotToQuad[2] = 3; // BackLeft   -> BottomRight
            slotToQuad[3] = 1; // BackRight  -> TopRight
            break;
        default:
            slotToQuad[0] = 0;
            slotToQuad[1] = 1;
            slotToQuad[2] = 2;
            slotToQuad[3] = 3;
            break;
    }

    // Quadrant pixel offsets within the cell
    float quadX[4] = {0.f, halfSize, 0.f, halfSize};
    float quadY[4] = {0.f, 0.f, halfSize, halfSize};

    for (const auto& member : party.getMembers()) {
        int slotIdx = static_cast<int>(member.getSlot());
        int quad = slotToQuad[slotIdx];

        sf::RectangleShape shape({halfSize, halfSize});
        shape.setPosition({pos.x + padding + quadX[quad],
                           pos.y + padding + quadY[quad]});
        shape.setFillColor(toSfColor(member.getColor()));
        window_.draw(shape);
    }
}

sf::Vector2f Renderer::cellToPixel(int x, int y) const {
    return {static_cast<float>(x) * cellSize_, static_cast<float>(y) * cellSize_};
}

} // namespace render
