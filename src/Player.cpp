#include <iostream>
#include "Player.hpp"

Player::Player() {
	view.setSize(sf::Vector2f(Game::WINDOW_SIZE));
}

void Player::processEvent(const sf::Event &event) {
	if(event.type == sf::Event::KeyReleased) {
		walkingDirection = HorizontalDirections::NONE;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		walkingDirection = HorizontalDirections::LEFT;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		walkingDirection = HorizontalDirections::RIGHT;
}

void Player::update(float deltaTime) {
	velocity = sf::Vector2f();

	if(walkingDirection == HorizontalDirections::LEFT)
		velocity.x -= walkSpeed;
	else if(walkingDirection == HorizontalDirections::RIGHT)
		velocity.x += walkSpeed;

	velocity.y += gravity;

	velocity *= deltaTime;

	centerView();

	updateGroundCollider();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.setView(view);
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void Player::centerView() {
	sf::Vector2f textureSize = sf::Vector2f(sprite.getTexture()->getSize());
	view.setCenter(getPosition() + sf::Vector2f(textureSize.x / 2, textureSize.y / 2));
}

void Player::setTexture(const sf::Texture &texture) {
	sprite.setTexture(texture);
}

const sf::Texture* Player::getTexture() {
	return sprite.getTexture();
}

sf::FloatRect Player::getViewGlobalBounds() const {
	return sf::FloatRect(sf::Vector2f
			                     (view.getCenter().x - view.getSize().x / 2,
			                      view.getCenter().y - view.getSize().y / 2),
	                     view.getSize());
}

sf::FloatRect Player::getGlobalBounds() {
	return sf::FloatRect(getPosition(), sf::Vector2f(getTexture()->getSize()));
}

sf::Vector2f Player::getNextMove() const {
	return velocity;
}

sf::FloatRect Player::getGroundCollider() const {
	return groundCollider;
}

void Player::updateGroundCollider() {
	groundCollider.left = getGlobalBounds().left;
	groundCollider.top = getGlobalBounds().top + getGlobalBounds().width;
	groundCollider.width = getGlobalBounds().width;
	groundCollider.height = 0.5;
}

void Player::moveCloserTo(const sf::FloatRect &rect) {
	sf::FloatRect globalBounds = getGlobalBounds();
	if(globalBounds.left + globalBounds.width <= rect.left)
		setPosition(rect.left - globalBounds.width, globalBounds.top);
	else {
		setPosition(rect.left + rect.width, globalBounds.top);
	}
}
