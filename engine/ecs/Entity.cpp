#include "Entity.hpp"

std::unordered_set<std::string> Entity::Tags;
std::unordered_map<std::string, Entities> Entity::EntitiesGroupedByTags;

void Entity::CreateTags(const TagsList &tags) {
	assert(Entity::Tags.empty());
	Entity::Tags = tags;
}

Entities& Entity::GetEntitiesByTag(const std::string &tag) {
	assert(Entity::Tags.count(tag));
	return EntitiesGroupedByTags[tag];
}

Entity::Entity(const std::string &name, const std::string &tag, Entity *parent) {
	assert(Tags.count(tag));

	this->name = name;
	this->tag = tag;
	this->parent = parent;
}

void Entity::passEvent(const sf::Event &event) {
	for(auto& e : entities) {
		e.second->passEvent(event);
	}
	for(auto& c : components) {
		c.second->processEvent(event);
	}
}

void Entity::update(float deltaTime) {
	checkForDestroying();

	for(auto& e : entities) {
		if(e.second->active)
			e.second->update(deltaTime);
	}

	for(auto& c : components) {
		if(c.second->enabled)
			c.second->update(deltaTime);
	}
}

void Entity::checkForDestroying() {
	for(auto it = entities.begin(); it != entities.end();) {
		if(it->second->isReadyToDestroy())
			it = entities.erase(it);
		else
			++it;
	}

	for(auto it = components.begin(); it != components.end();) {
		if(it->second->isReadyToDestroy())
			it = components.erase(it);
		else
			++it;
	}
}

bool Entity::hasEntity(const std::string &name) {
	return entities.count(name) == 1;
}

void Entity::addEntity(const std::string &name, const std::string& tag) {
	assert(!hasEntity(name));

	entities[name] = std::make_unique<Entity>(name, tag, this);
	EntitiesGroupedByTags[tag].insert(entities[name]);
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

std::string Entity::getTag() const {
	return tag;
}

void Entity::setTag(const std::string& tag) {
	assert(Entity::Tags.count(tag));

	std::string oldTag = this->tag;
	this->tag = tag;

	std::shared_ptr<Entity> sharedPtrToThis = parent->entities[name];

	Entity::EntitiesGroupedByTags[tag].insert(sharedPtrToThis);
	Entity::EntitiesGroupedByTags[oldTag].erase(sharedPtrToThis);
}