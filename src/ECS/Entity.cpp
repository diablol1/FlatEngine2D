#include "Entity.hpp"

std::unordered_set<std::string> Entity::tags;
std::unordered_map<std::string, Entities> Entity::entitiesGroupedByTags;

void Entity::createTags(const TagsList& tags) {
	assert(Entity::tags.empty());
	Entity::tags = tags;
}

Entities& Entity::getEntitiesByTag(const std::string &tag) {
	assert(Entity::tags.count(tag));
	return entitiesGroupedByTags[tag];
}

Entity::Entity(const std::string &name, const std::string &tag, Entity *parent) {
	assert(tags.count(tag));

	this->name = name;
	this->tag = tag;
	this->parent = parent;
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
	entitiesGroupedByTags[tag].insert(entities[name]);
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
	assert(Entity::tags.count(tag));

	std::string oldTag = this->tag;
	this->tag = tag;

	std::shared_ptr<Entity> sharedPtrToThis = parent->entities[name];

	Entity::entitiesGroupedByTags[tag].insert(sharedPtrToThis);
	Entity::entitiesGroupedByTags[oldTag].erase(sharedPtrToThis);
}