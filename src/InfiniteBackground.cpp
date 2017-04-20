#include "InfiniteBackground.hpp"


void InfiniteBackground::moveBackToFront() {
	backgrounds[0].move(backgrounds[0].getTexture()->getSize().x * 2, 0);
	std::swap(backgrounds[0], backgrounds[1]);
}

void InfiniteBackground::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for(const auto& background : backgrounds) {
		target.draw(background);
	}
}

void InfiniteBackground::setPosition(const sf::Vector2f &position) {
	backgrounds[0].setPosition(position.x - getTexture()->getSize().x, position.y);
	backgrounds[1].setPosition(position);
}

void InfiniteBackground::setTexture(const sf::Texture &texture) {
	for(auto& background : backgrounds) {
		background.setTexture(texture);
	}
}

const sf::Texture *InfiniteBackground::getTexture() const {
	return backgrounds[0].getTexture(); //Backgrounds[1]'s texture can be returned as well
}

sf::Vector2f InfiniteBackground::getPosition() const {
	return backgrounds[0].getPosition();
}