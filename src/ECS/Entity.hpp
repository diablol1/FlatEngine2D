#pragma once

#include <cassert>
#include <unordered_map>
#include <memory>
#include <unordered_set>

#include "Component.hpp"
#include "Destroyable.hpp"

using Entities = std::unordered_set<std::shared_ptr<Entity>>;
using TagsList = std::initializer_list<std::string>;

class Entity : public Destroyable {
public:
	static void createTags(const TagsList& tags);
	static Entities& getEntitiesByTag(const std::string& tag);

	Entity(const std::string &name, const std::string &tag, Entity *parent);

	void update(float deltaTime);

	template<typename ComponentType>
	bool hasComponent() const {
		return components.count(getComponentHashCode<ComponentType>()) == 1;
	}

	template<typename ComponentType>
	void addComponent() {
		static_assert(std::is_base_of<Component, ComponentType>::value);
		assert(!hasComponent<ComponentType>());

		components[getComponentHashCode<ComponentType>()] = std::make_shared<ComponentType>();
		getComponent<ComponentType>().entity = this;
		getComponent<ComponentType>().init();
	}

	template<typename ComponentType>
	ComponentType& getComponent() {
		assert(hasComponent<ComponentType>());

		return *std::dynamic_pointer_cast<ComponentType>(components[getComponentHashCode<ComponentType>()]);
	}

	template<typename ComponentType>
	std::size_t getComponentHashCode() const {
		return typeid(ComponentType).hash_code();
	}

	bool hasEntity(const std::string& name);

	void addEntity(const std::string& name, const std::string& tag);

	Entity& getEntity(const std::string& name);

	void setName(const std::string& name);
	std::string getName() const;

	void setTag(const std::string& tag);
	std::string getTag() const;

private:

	static std::unordered_set<std::string> tags;
	static std::unordered_map<std::string, Entities> entitiesGroupedByTags;

	std::unordered_map<std::size_t, std::shared_ptr<Component>> components;
	std::unordered_map<std::string, std::shared_ptr<Entity>> entities;

	std::string name;
	std::string tag;

	Entity* parent;

	void checkForDestroying();
};

