#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

class PlayState final : public GameState {
public:
	void processEvent(const sf::Event &event, std::shared_ptr<GameState> current, GameStatesMap other) override;
	void update(float deltaTime) override;

protected:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

