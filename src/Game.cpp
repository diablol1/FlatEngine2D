#include "Game.h"


Game::Game() : window(sf::VideoMode(800, 600),
	"Platformer2D", sf::Style::Close | sf::Style::Titlebar)
{

}

void Game::run()
{
	while (window.isOpen())
	{
		processEvents();
		draw();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::draw()
{
	window.clear();

	window.display();
}
