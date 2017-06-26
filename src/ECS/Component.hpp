#pragma once

#include "Destroyable.hpp"

class Entity;

class Component : public Destroyable {
public:
	Entity* entity;

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;

	bool enabled = true;
};

