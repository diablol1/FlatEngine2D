#pragma once

#include <string>

#include "json.hpp"
#include "Player.hpp"

using json = nlohmann::json;

class Level : public sf::Drawable {
public:
	void loadFromFile(const std::string& fileName);
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void scaleBackgroundToWindow();
};

