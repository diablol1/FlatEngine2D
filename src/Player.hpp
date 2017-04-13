#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable {
public:
	Player(float moveSpeed);

	void processEvent(const sf::Event& event);
	void update(float deltaTime);

	void setTexture(const sf::Texture &texture);
protected:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	sf::Sprite sprite;

	float moveSpeed;
	bool hasMovedFlag;
};

