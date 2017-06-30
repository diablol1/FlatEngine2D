#include "Game.hpp"

Game::Game(unsigned int width, unsigned int height, const std::string &title, sf::Uint32 style) :
	window(sf::VideoMode(width, height), title, style),
	scene("Scene", "Scene", nullptr) {
}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while(window.isOpen()) {
		detectAndPassEvent();
		timeSinceLastUpdate += clock.restart();

		while(timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;
			detectAndPassEvent();
			scene.update(TIME_PER_FRAME.asSeconds());
		}
		//Drawing will be here
	}
}

void Game::detectAndPassEvent() {
	sf::Event event;
	while(window.pollEvent(event)) {
		if(event.type == sf::Event::Closed)
			window.close();

		scene.passEvent(event);
	}
}