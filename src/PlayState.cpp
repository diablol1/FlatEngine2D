#include "PlayState.hpp"

void PlayState::processEvent(const sf::Event &event, std::shared_ptr<GameState> current, GameStatesMap other) {
	level.processEvent(event);
}

void PlayState::update(float deltaTime) {
	level.update(deltaTime);
}

void PlayState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(level);
}
