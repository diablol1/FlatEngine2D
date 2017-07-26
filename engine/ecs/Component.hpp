#pragma once

#include <SFML/Graphics.hpp>

#include <any>

#include "Destroyable.hpp"

class Entity;

/*NOTE:
 * Component which uses another component has to be added as the second one
 * E.g. Adding Collider after Position, because Collider needs Position
 * Scripts should be added after normal components
*/

class Component : public Destroyable {
    friend class Entity;
public:
    bool enabled = true;
protected:
	Entity* entity;

	virtual void init() {}
	virtual void update(float deltaTime) {}
	virtual void processEvent(const sf::Event& event) {}

    virtual void onMessage(const std::string& message, const std::any& value) {}
};

