#pragma once

#include <SFML/Graphics.hpp>

class InfiniteBackground : public sf::Drawable {
public:
	void moveBackToFront();

	void setPosition(const sf::Vector2f& position);
	void setTexture(const sf::Texture& texture);

	const sf::Texture* getTexture() const;
	sf::Vector2f getPosition() const;
private:
	std::array<sf::Sprite, 2> backgrounds;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};