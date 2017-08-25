#include "Entity.hpp"

std::unordered_set<std::string> Entity::Tags;
std::unordered_map<std::string, Entities> Entity::EntitiesGroupedByTags;
Entity* Entity::Root;

void Entity::CreateTags(const TagsList &tags) {
	assert(Entity::Tags.empty());
	Entity::Tags = tags;
}

Entities& Entity::GetEntitiesByTag(const std::string &tag) {
	assert(Entity::Tags.count(tag));
	return EntitiesGroupedByTags[tag];
}

Entity &Entity::GetRoot() {
	if(Root == nullptr) {
		std::cerr << "Root doesn't exist. Entity isn't created";
	}
	else
		return *Root;
}

Entity::Entity(const std::string &name, const std::string &tag, Entity *parent) {
	if(parent == nullptr)
		Root = this;

	assert(Tags.count(tag));

	this->name = name;
	this->tag = tag;
	this->parent = parent;

    addComponent<Transform>();
}

void Entity::saveToFile(const std::string &filename) {
	json jsonData;
	serialize(jsonData);

	std::ofstream file("../game/scenes/" + filename);
    file << jsonData.dump(2);
	file.close();
}

void Entity::loadFromFile(const std::string &filename) {
    std::ifstream file("../game/scenes/" + filename);

    if(file.is_open()) {
        entities.clear();
        components.clear();

        json jsonData;
        file >> jsonData;
        file.close();

        deserialize(jsonData);
    }
    else
        std::cerr << "Scene " << filename << " couldn't be loaded";
}

void Entity::serialize(json &jsonData) const {
    jsonData["name"] = name;
    jsonData["tag"] = tag;
    jsonData["active"] = active;

    for(const auto& c : components) {
		std::string componentName = utility::getClassName(*c.second);

        c.second->serialize(jsonData["components"][componentName]);
        jsonData["components"][componentName]["enabled"] = c.second->enabled;
    }

	for(const auto& e : entities) {
		e.second->serialize(jsonData["entities"][e.second->getName()]);
	}
}

void Entity::deserialize(const json& jsonData) {
    setName(jsonData["name"]);
    setTag(jsonData["tag"]);
    active = jsonData["active"];

    if(jsonData.count("components")) {
        for(auto it = jsonData["components"].begin(); it != jsonData["components"].end(); ++it) {
            std::string componentName = it.key();
            auto componentFields = it.value();

            std::shared_ptr<Component> component = ComponentsCreator::GetInstance().create(componentName);

            component->entity = this;
            component->deserialize(componentFields);

            component->enabled = componentFields["enabled"];

            components[utility::getClassHashCode(*component)] = component;
        }
    }

    if(jsonData.count("entities")) {
        for(const auto& j : jsonData["entities"]) {
            addEntity("tmpName", "Default");
            getEntity("tmpName").deserialize(j);
        }
    }
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

	for(auto& c : components) {
		if(c.second->enabled)
			c.second->update(deltaTime);
	}

    for(auto& e : entities) {
        if(e.second->active)
            e.second->update(deltaTime);
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
    if (this->name != name) {
        if (parent == nullptr)
            this->name = name;
        else {
            std::string oldName = this->name;
            this->name = name;

            parent->entities[name] = parent->entities[oldName];
            parent->entities.erase(oldName);
        }
    }
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

	Entity::EntitiesGroupedByTags[tag].insert(shared_from_this());
	Entity::EntitiesGroupedByTags[oldTag].erase(shared_from_this());
}

Entity* Entity::getParent() {
    return parent;
}

std::unordered_map<std::string, std::shared_ptr<Entity>> &Entity::getEntities() {
    return entities;
}