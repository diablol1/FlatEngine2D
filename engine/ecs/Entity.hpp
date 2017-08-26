#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cassert>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include <any>
#include <fstream>

#include "common/utility.hpp"
#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "ecs/Destroyable.hpp"
#include "ecs/Serializable.hpp"

using Entities = std::unordered_set<std::shared_ptr<Entity>>;
using TagsList = std::initializer_list<std::string>;

class Entity : public Destroyable, private Serializable, public std::enable_shared_from_this<Entity> {
public:
    bool active = true;

	static void CreateTags(const TagsList &tags);
	static Entities& GetEntitiesByTag(const std::string &tag);
	static Entity& GetRoot();

	Entity(const std::string &name, const std::string &tag, Entity *parent);

    void saveToFile(const std::string &filename);
    void loadFromFile(const std::string &filename);

    void serialize(json &jsonData) const override;

	void passEvent(const sf::Event& event);
	void update(float deltaTime);
	void drawSprites(sf::RenderWindow& window);

	template<typename ComponentType>
	bool hasComponent() const {
		return components.count(utility::getClassHashCode<ComponentType>()) == 1;
	}

	template<typename ComponentType, typename... TArgs>
	void addComponent(TArgs... args) {
		static_assert(std::is_base_of<Component, ComponentType>::value);
		assert(!hasComponent<ComponentType>());

		components[utility::getClassHashCode<ComponentType>()] = std::make_shared<ComponentType>(args...);
		getComponent<ComponentType>().entity = this;
		getComponent<ComponentType>().init();
	}

	template<typename ComponentType>
	void sendMessage(const std::string& message, const std::any& value) {
		getComponent<ComponentType>().onMessage(message, value);
	}

	template<typename ComponentType>
	ComponentType& getComponent() {
		assert(hasComponent<ComponentType>());

		return *std::dynamic_pointer_cast<ComponentType>(components[utility::getClassHashCode<ComponentType>()]);
	}

	bool hasEntity(const std::string& name);

	void addEntity(const std::string& name, const std::string& tag);

	Entity& getEntity(const std::string& name);

	void setName(const std::string& name);
	std::string getName() const;

	void setTag(const std::string& tag);
	std::string getTag() const;

    void deserialize(const json& jsonData) override;

    Entity* getParent();
    std::unordered_map<std::string, std::shared_ptr<Entity>>& getEntities();
private:

	static std::unordered_set<std::string> Tags;
	static std::unordered_map<std::string, Entities> EntitiesGroupedByTags;
	static Entity* Root;

	std::unordered_map<std::size_t, std::shared_ptr<Component>> components;
	std::unordered_map<std::string, std::shared_ptr<Entity>> entities;

	std::string name;
	std::string tag;

	Entity* parent;

	void checkForDestroying();
};