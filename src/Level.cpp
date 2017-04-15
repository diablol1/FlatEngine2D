#include "Level.hpp"

Level::Level() {
	//Reading it from file might be better
	textures["player"].loadFromFile("data/sprites/player.png");
	player.setTexture(textures["player"]);
	player.setMoveSpeed(5);
}

void Level::loadFromFile(const std::string &fileName) {
	std::ifstream fileWithLevelData(fileName);
	json js(fileWithLevelData);

	textures["background"].loadFromFile(js["background"]["path"]);
	background.setTexture(textures["background"]);
	scaleBackgroundToWindow();

	player.setPosition(js["player"]["position"]["x"],
	                   js["player"]["position"]["y"]);
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(player);
}

void Level::scaleBackgroundToWindow() {
	background.setScale(static_cast<float>(Game::WINDOW_SIZE.x) / textures["background"].getSize().x,
	                    static_cast<float>(Game::WINDOW_SIZE.y) / textures["background"].getSize().y);
}

void Level::processEvent(const sf::Event &event) {
	player.processEvent(event);
}

void Level::update(float deltaTime) {
	player.update(deltaTime);
}