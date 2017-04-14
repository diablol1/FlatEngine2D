#include <fstream>
#include "Level.hpp"
#include "Game.hpp"

void Level::loadFromFile(const std::string &fileName) {
	std::ifstream fileWithLevelData(fileName);
	json js(fileWithLevelData);

	backgroundTexture.loadFromFile(js["background"]["path"]);
	background.setTexture(backgroundTexture);
	scaleBackgroundToWindow();
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
}

void Level::scaleBackgroundToWindow() {
	background.setScale(static_cast<float>(Game::WINDOW_SIZE.x) / backgroundTexture.getSize().x,
	                    static_cast<float>(Game::WINDOW_SIZE.y) / backgroundTexture.getSize().y);
}
