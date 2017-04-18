#pragma once

#include <SFML/Graphics.hpp>

#include "Game.hpp"

class Player : public sf::Drawable, public sf::Transformable {
public:
	Player();

	void centerView();

	void processEvent(const sf::Event& event);
	void update(float deltaTime);

	void setTexture(const sf::Texture &texture);
	void setMoveSpeed(int speed);
private:
	sf::Sprite sprite;

	sf::View view;

	float moveSpeed;
	bool hasMovedFlag;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

