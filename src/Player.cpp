#include "Player.hpp"

Player::Player() {
	view.setSize(sf::Vector2f(Game::WINDOW_SIZE));
}

void Player::processEvent(const sf::Event &event) {
	if(event.type == sf::Event::KeyReleased) {
		walkingDirection = WalkingDirections::NONE;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		walkingDirection = WalkingDirections::LEFT;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		walkingDirection = WalkingDirections::RIGHT;
}

void Player::update(float deltaTime) {
	if(walkingDirection == WalkingDirections::LEFT)
		nextMove.x -= moveSpeed;
	else if(walkingDirection == WalkingDirections::RIGHT)
		nextMove.x += moveSpeed;

	nextMove.y += gravity;

	nextMove *= deltaTime;
	move(nextMove);
	nextMove = sf::Vector2f();

	centerView();
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

void Player::setMoveSpeed(int speed) {
	moveSpeed = speed;
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
