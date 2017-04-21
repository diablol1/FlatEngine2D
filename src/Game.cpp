#include "Game.hpp"
#include "PlayState.hpp"

const sf::Vector2i Game::WINDOW_SIZE = sf::Vector2i(800, 600);

Game::Game()
    : window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Platformer2D",
             sf::Style::Close | sf::Style::Titlebar) {

		states[gs::GameStates::PLAY] = std::make_shared<PlayState>();

		currentState = states[gs::GameStates::PLAY];
	}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {
        processEvents();
	    timeSinceLastUpdate += clock.restart();
	    while(timeSinceLastUpdate > TIME_PER_FRAME) {
		    timeSinceLastUpdate -= TIME_PER_FRAME;
		    processEvents();
		    update(TIME_PER_FRAME.asSeconds());
	    }
	    draw();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
	    if (event.type == sf::Event::Closed)
		     window.close();
	    else
		    currentState->processEvent(event, currentState, states);
  }
}

void Game::draw() {
    window.clear();

	window.draw(*currentState);

    window.display();
}

void Game::update(float deltaTime) {
	currentState->update(deltaTime);
}
