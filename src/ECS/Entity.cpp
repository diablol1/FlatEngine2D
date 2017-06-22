#include "Entity.hpp"

std::set<std::string> Entity::tags;
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
	for(auto& c : components) {
		std::any_cast<Component&>(c.second).update(deltaTime);
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

void Entity::deleteEntity(const std::string &name) {
	assert(hasEntity(name));

	Entities& e = getEntitiesByTag(entities[name]->tag);
	e.erase(entities[name]);
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