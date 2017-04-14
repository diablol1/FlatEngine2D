#include "Player.hpp"


void Player::processEvent(const sf::Event &event) {
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::A:
				move(-moveSpeed, 0);
				hasMovedFlag = true;
				break;
			case sf::Keyboard::D:
				move(moveSpeed, 0);
				hasMovedFlag = true;
				break;
		}
	}
}

void Player::update(float deltaTime) {
	if(hasMovedFlag) {
		setPosition(getPosition() * deltaTime);
		hasMovedFlag = false;
	}
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void Player::setTexture(const sf::Texture &texture) {
	sprite.setTexture(texture);
}

void Player::setMoveSpeed(int speed) {
	moveSpeed = speed;
}

