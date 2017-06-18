#pragma once

struct Component {
	class Entity* entity;

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
};

