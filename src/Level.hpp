#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

#include "json.hpp"
#include "Player.hpp"
#include "Game.hpp"

using json = nlohmann::json;

class Level : public sf::Drawable {
public:
	Level();
	void loadFromFile(const std::string& fileName);

	void processEvent(const sf::Event& event);
	void update(float deltaTime);
private:
	sf::Sprite background;
	Player player;

	std::unordered_map<std::string, sf::Texture> textures;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void scaleBackgroundToWindow();
};

