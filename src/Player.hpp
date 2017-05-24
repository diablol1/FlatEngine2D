#pragma once

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "InfiniteBackground.hpp"

class Player : public sf::Drawable, public sf::Transformable {
public:
	Player();

	void centerView();

	void processEvent(const sf::Event& event);
	void update(float deltaTime);

	void setTexture(const sf::Texture& texture);
	void setMoveSpeed(int speed);
	const sf::Texture* getTexture();
	sf::FloatRect getViewGlobalBounds() const;
private:
	sf::Sprite sprite;

	sf::View view;

	sf::Vector2f nextMove;
	float moveSpeed;
	int gravity = 5;

	WalkingDirections walkingDirection;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

