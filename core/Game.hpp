#pragma once

#include "ecs/Entity.hpp"

class Game {
public:
    std::shared_ptr<Entity> scene;

    Game(unsigned int width, unsigned int height, const std::string& title, sf::Uint32 style);
    void run();
private:
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

    std::shared_ptr<sf::RenderWindow> window;

    void detectAndPassEvent();
    void draw();
};