#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameState.hpp"

class Game {
public:
	static const sf::Vector2i WINDOW_SIZE;
    Game();

    void run();
private:
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::RenderWindow window;

	std::shared_ptr<GameState> currentState;
	GameStatesMap states;

    void processEvents();
	void update(float deltaTime);
    void draw();
};
