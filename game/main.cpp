#include <Game.hpp>

int main() {
	Entity::CreateTags({"Scene", "Default"});

	Game game(800, 600, "Platformer2D", sf::Style::Close | sf::Style::Titlebar);

	game.run();
}