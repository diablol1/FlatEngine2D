#include "Level.hpp"

Level::Level() : background(2) {
	//Reading it from file might be better
	textures["player"].loadFromFile("data/sprites/player.png");
	player.setTexture(textures["player"]);
	player.setMoveSpeed(600);

	loadFromFile("data/levels/level1/level1.json");
}

void Level::loadFromFile(const std::string &fileName) {
	std::ifstream fileWithLevelData(fileName);
	json js(fileWithLevelData);
	fileWithLevelData.close();

	textures["background"].loadFromFile(js["background"]["texturePath"]);
	background.setTexture(textures["background"]);

	player.setPosition(js["player"]["position"]["x"],
	                   js["player"]["position"]["y"]);
	player.centerView();

	background.setPosition(player.getPosition() - sf::Vector2f(background.getTexture()->getSize().x / 2,
	                                                           background.getTexture()->getSize().y / 2));

	loadTiles(js);
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

void Level::processEvent(const sf::Event &event) {
	player.processEvent(event);
}

void Level::update(float deltaTime) {
	player.update(deltaTime);
	if(player.getViewGlobalBounds().left < background.getParts()[0].getGlobalBounds().left)
		background.moveFrontToBack();
	if(player.getViewGlobalBounds().left > background.getParts()[1].getGlobalBounds().left)
		background.moveBackToFront();
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(player);
	for(auto const& tile : tiles) {
		target.draw(tile, states);
	}
}