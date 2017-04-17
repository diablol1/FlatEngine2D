#include "Level.hpp"

Level::Level() {
	//Reading it from file might be better
	loadFromFile("data/levels/level1/level1.json");
	textures["player"].loadFromFile("data/sprites/player.png");
	player.setTexture(textures["player"]);
	player.setMoveSpeed(5);
}

void Level::loadFromFile(const std::string &fileName) {
	std::ifstream fileWithLevelData(fileName);
	json js(fileWithLevelData);
	fileWithLevelData.close();

	textures["background"].loadFromFile(js["background"]["texturePath"]);
	background.setTexture(textures["background"]);
	scaleBackgroundToWindow();

	player.setPosition(js["player"]["position"]["x"],
	                   js["player"]["position"]["y"]);

	loadTiles(js);
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(player);
	for(auto const& tile : tiles) {
		target.draw(tile, states);
	}
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

void Level::loadTiles(const json &js) {
	tileSize.x = js["tileSize"]["x"];
	tileSize.y = js["tileSize"]["y"];

	for(const auto& tileSet : js["tiles"]) {
		std::string textureName = tileSet["data"]["name"];
		if(textures.count(textureName) == 0) {
			sf::Texture tmpTexture;
			tmpTexture.loadFromFile(tileSet["data"]["texturePath"]);
			textures[textureName] = tmpTexture;
		}

		for (const auto &tile : tileSet["objects"]) {
			sf::Sprite tmpTile(textures[textureName]);
			tmpTile.setPosition(static_cast<int>(tile["positionInTiles"]["x"]) * tileSize.x,
			                    static_cast<int>(tile["positionInTiles"]["y"]) * tileSize.y);
			tiles.push_back(tmpTile);
		}
	}
}
