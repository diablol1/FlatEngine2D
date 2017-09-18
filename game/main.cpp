#include <Game.hpp>

int main() {
	Game game(800, 600, "FlatEngine2D", sf::Style::Close | sf::Style::Titlebar);

	game.run();
}