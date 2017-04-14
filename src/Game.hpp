#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameState.hpp"

class Game {
public:
	static const sf::Vector2i windowSize;

    Game();

    void run();
private:
    sf::RenderWindow window;

	std::shared_ptr<GameState> currentState;
	GameStatesMap states;

    void processEvents();
	void update(float deltaTime);
    void draw();
};
