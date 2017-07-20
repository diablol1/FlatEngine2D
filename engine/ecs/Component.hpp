#pragma once

#include <SFML/Graphics.hpp>

#include "Destroyable.hpp"

class Entity;

/*NOTE:
 * Component which uses another component has to be added as the second one
 * E.g. Adding Collider after Position, because Collider needs Position
 * Scripts should be added after normal components
*/

class Component : public Destroyable {
public:
	Entity* entity;

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;

	virtual void processEvent(const sf::Event& event) {}

	bool enabled = true;
};

