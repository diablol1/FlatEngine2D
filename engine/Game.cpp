#include "Game.hpp"

Game::Game(unsigned int width, unsigned int height, const std::string& title, sf::Uint32 style) {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, style);
    Camera::window = window;

    Entity::LoadTagsFromFile("../game/tags.txt");
    scene = std::make_shared<Entity>("Scene", "Scene", nullptr);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window->isOpen()) {
        detectAndPassEvent();
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TIME_PER_FRAME) {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            detectAndPassEvent();
            scene->update(TIME_PER_FRAME.asSeconds());
        }
        draw();
    }
}

void Game::detectAndPassEvent() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

        scene->passEvent(event);
    }
}

void Game::draw() {
    window->clear();
    scene->drawSprites(window);
    window->display();
}