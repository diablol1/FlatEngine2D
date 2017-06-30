#pragma once

#include <SFML/Graphics.hpp>

#include <ecs/Entity.hpp>

class Game {
public:
	Game(unsigned int width, unsigned int height, const std::string& title, sf::Uint32 style);
	void run();

	Entity scene;
private:
	void detectAndPassEvent();

	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

	sf::RenderWindow window;
};

