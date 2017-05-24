#include <iostream>
#include "InfiniteBackground.hpp"

InfiniteBackground::InfiniteBackground(int numberOfParts) {
	for(int i = 0; i < numberOfParts; i++) {
		parts.push_back(sf::Sprite());
	}
}

void InfiniteBackground::moveBackToFront() {
	parts[0].move(static_cast<int>(getTexture()->getSize().x) * 2, 0);
	std::swap(parts[0], parts[1]);
}

void InfiniteBackground::moveFrontToBack() {
	parts[1].move(static_cast<int>(getTexture()->getSize().x) * -2, 0);
	std::swap(parts[0], parts[1]);
}

void InfiniteBackground::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for(const auto& part : parts) {
		target.draw(part);
	}
	std::cout << static_cast<int>(getTexture()->getSize().x) * 2 << std::endl;
}

void InfiniteBackground::setPosition(const sf::Vector2f &position) {
	parts[0].setPosition(position.x - getTexture()->getSize().x, position.y);
	parts[1].setPosition(position);
}

void InfiniteBackground::setTexture(const sf::Texture &texture) {
	for(auto& background : parts) {
		background.setTexture(texture);
	}
}

const sf::Texture *InfiniteBackground::getTexture() const {
	return parts[0].getTexture(); //Backgrounds[1]'s texture can be returned as well
}

const std::vector<sf::Sprite> &InfiniteBackground::getParts() {
	return parts;
}