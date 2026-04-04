#pragma once

#include "Grid.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

class GameObject {
public:
    GameObject(int id, int gridX, int gridY, sf::Color color, int moveInterval);
    virtual ~GameObject() = default;

    virtual void onTick(Grid& grid, int currentTick) = 0;
    virtual void onCollision(GameObject& other) = 0;

    void moveTo(Grid& grid, int newX, int newY, int currentTick);
    void snapshotPosition();
    void render(sf::RenderWindow& window, const Grid& grid, float alpha) const;

    int getId() const;
    int getGridX() const;
    int getGridY() const;
    bool canMove(int currentTick) const;

protected:
    int id_;
    int gridX_, gridY_;
    int prevGridX_, prevGridY_;
    int moveInterval_;
    int lastMoveTick_ = -999;
    sf::Color color_;
};
