#include "Player.hpp"

Player::Player() {
	view.setSize(sf::Vector2f(Game::WINDOW_SIZE));
}

void Player::processEvent(const sf::Event &event) {
	if(event.type == sf::Event::KeyReleased) {
		movingDirection = MovingDirections::NONE;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movingDirection = MovingDirections::LEFT;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movingDirection = MovingDirections::RIGHT;
}
void Player::update(float deltaTime) {
	if(movingDirection == MovingDirections::LEFT)
		nextMove.x -= moveSpeed;
	else if(movingDirection == MovingDirections::RIGHT)
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

bool Player::isViewStuckOutOfBackground(const InfiniteBackground& background) {
	return (view.getSize().x / 2 >
	    background.getPosition().x +
	    background.getTexture()->getSize().x * 2 -
	    getPosition().x -
	    getTexture()->getSize().x / 2);
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

