#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <unordered_map>

#include "Enums.hpp"
#include "EnumClassHash.hpp"

using GameStatesMap = std::unordered_map<gs::GameStates, std::shared_ptr<class GameState>, EnumClassHash>;

class GameState : public sf::Drawable {
public:
	virtual void processEvent(const sf::Event& event, std::shared_ptr<GameState> current, GameStatesMap other) = 0;
	virtual void update(float deltaTime) = 0;
};