#pragma once

#include <string>

#include "json.hpp"
#include "Player.hpp"

using json = nlohmann::json;

class Level : public sf::Drawable {
public:
	Level();
	void loadFromFile(const std::string& fileName);

	void processEvent(const sf::Event& event);
	void update(float deltaTime);
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture playerTexture;
	Player player;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void scaleBackgroundToWindow();
};

