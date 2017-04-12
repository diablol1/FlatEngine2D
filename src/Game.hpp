#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameState.hpp"

class Game {
public:
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
