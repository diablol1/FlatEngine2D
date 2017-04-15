#include <fstream>
#include "Level.hpp"
#include "Game.hpp"


Level::Level() {
	//TODO: Reading from file would be better
	playerTexture.loadFromFile("data/sprites/player.png");
	player.setTexture(playerTexture);
	player.setMoveSpeed(5);
}

void Level::loadFromFile(const std::string &fileName) {
	std::ifstream fileWithLevelData(fileName);
	json js(fileWithLevelData);

	backgroundTexture.loadFromFile(js["background"]["path"]);
	background.setTexture(backgroundTexture);
	scaleBackgroundToWindow();

	player.setPosition(js["player"]["position"]["x"],
	                   js["player"]["position"]["y"]);
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(player);
}

void Level::scaleBackgroundToWindow() {
	background.setScale(static_cast<float>(Game::WINDOW_SIZE.x) / backgroundTexture.getSize().x,
	                    static_cast<float>(Game::WINDOW_SIZE.y) / backgroundTexture.getSize().y);
}

void Level::processEvent(const sf::Event &event) {
	player.processEvent(event);
}

void Level::update(float deltaTime) {
	player.update(deltaTime);
}
