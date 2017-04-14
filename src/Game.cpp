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
    while (window.isOpen()) {
        processEvents();
	    update(0); //I haven't implemented calculating delta time yet
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
