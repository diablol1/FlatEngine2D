#pragma once

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "InfiniteBackground.hpp"

class Player : public sf::Drawable, public sf::Transformable {
public:
	float walkSpeed;
	float gravity;

	Player();

	void processEvent(const sf::Event& event);
	void update(float deltaTime);
	void centerView();

	void moveCloserTo(const sf::FloatRect &rect);

	void setTexture(const sf::Texture& texture);

 	const sf::Texture* getTexture();
	sf::FloatRect getViewGlobalBounds() const;
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getVelocity() const;
	sf::FloatRect getGroundCollider() const;

private:
	sf::FloatRect groundCollider;

	sf::Sprite sprite;

	sf::View view;

	sf::Vector2f velocity;

	HorizontalDirections walkingDirection;

	void updateGroundCollider();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

