#include "game/Game.hpp"
#include <SFML/Window/Event.hpp>

Game::Game()
    : window_(sf::VideoMode(768, 576), "Critical Miss"),
      grid_(16, 12, 48.f) {

    window_.setVerticalSyncEnabled(true);

    player_ = std::make_unique<Player>(0, 1, 1);
    grid_.place(player_->getId(), player_->getGridX(), player_->getGridY());

    auto enemy = std::make_unique<Enemy>(1, 14, 10, 2);
    grid_.place(enemy->getId(), enemy->getGridX(), enemy->getGridY());
    enemies_.push_back(std::move(enemy));

    allObjects_.push_back(player_.get());
    for (auto& e : enemies_)
        allObjects_.push_back(e.get());
}

void Game::run() {
    sf::Clock clock;
    float accumulator = 0.f;

    while (window_.isOpen()) {
        float dt = clock.restart().asSeconds();
        accumulator += dt;
        if (accumulator > MAX_ACCUMULATOR)
            accumulator = MAX_ACCUMULATOR;

        processEvents();

        while (accumulator >= TICK_DURATION) {
            tick();
            accumulator -= TICK_DURATION;
        }

        float alpha = accumulator / TICK_DURATION;
        render(alpha);
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window_.close();

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::W: case sf::Keyboard::Up:
                case sf::Keyboard::S: case sf::Keyboard::Down:
                case sf::Keyboard::A: case sf::Keyboard::Left:
                case sf::Keyboard::D: case sf::Keyboard::Right:
                    player_->bufferInput(event.key.code);
                    break;
                case sf::Keyboard::Escape:
                    window_.close();
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::tick() {
    // Pass 1: snapshot previous positions
    for (auto* obj : allObjects_)
        obj->snapshotPosition();

    // Set enemy targets before processing
    for (auto& enemy : enemies_)
        enemy->setTarget(player_->getGridX(), player_->getGridY());

    // Pass 2: process tick logic (player first)
    for (auto* obj : allObjects_)
        obj->onTick(grid_, currentTick_);

    currentTick_++;
}

void Game::render(float alpha) {
    window_.clear(sf::Color(30, 30, 30));
    drawGrid();

    for (auto* obj : allObjects_)
        obj->render(window_, grid_, alpha);

    window_.display();
}

void Game::drawGrid() {
    float w = grid_.getWidth() * grid_.getCellSize();
    float h = grid_.getHeight() * grid_.getCellSize();
    sf::Color lineColor(60, 60, 60);

    for (int x = 0; x <= grid_.getWidth(); x++) {
        sf::RectangleShape line({1.f, h});
        line.setPosition(x * grid_.getCellSize(), 0.f);
        line.setFillColor(lineColor);
        window_.draw(line);
    }

    for (int y = 0; y <= grid_.getHeight(); y++) {
        sf::RectangleShape line({w, 1.f});
        line.setPosition(0.f, y * grid_.getCellSize());
        line.setFillColor(lineColor);
        window_.draw(line);
    }
}
