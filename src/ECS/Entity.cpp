#include "Entity.hpp"

Entity::Entity(const std::string &name, Entity* parent) {
	this->parent = parent;
	this->name = name;
}

void Entity::update(float deltaTime) {
	for(auto& c : components) {
		std::any_cast<Component&>(c.second).update(deltaTime);
	}
}

bool Entity::hasEntity(const std::string &name) {
	return entities.count(name) == 1;
}

void Entity::addEntity(const std::string &name) {
	assert(!hasEntity(name));

	entities[name] = std::make_unique<Entity>(name, this);
}

void Entity::deleteEntity(const std::string &name) {
	assert(hasEntity(name));

	entities.erase(name);
}

Entity &Entity::getEntity(const std::string &name) {
	assert(hasEntity(name));

	return *entities[name];
}

void Entity::setName(const std::string& name) {
	assert(!parent->hasEntity(name));

	std::string oldName = this->name;
	this->name = name;

	parent->entities[name] = parent->entities[oldName];
	parent->entities.erase(oldName);
}

std::string Entity::getName() const {
	return name;
}
