#pragma once

#include <SFML/Graphics.hpp>

class InfiniteBackground : public sf::Drawable {
public:
	InfiniteBackground(int numberOfParts);

	void moveBackToFront();
	void moveFrontToBack();

	void setPosition(const sf::Vector2f& position);
	void setTexture(const sf::Texture& texture);

	const std::vector<sf::Sprite>& getParts();
	const sf::Texture* getTexture() const;
private:
	std::vector<sf::Sprite> parts;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};