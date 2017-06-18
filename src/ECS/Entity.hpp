#pragma once

#include <cassert>
#include <any>
#include <unordered_map>
#include <memory>

#include "Component.hpp"

class Entity {
public:
	Entity(const std::string& name);

	void update(float deltaTime);

	template<typename ComponentType>
	bool hasComponent() const {
		return components.count(getComponentHashCode<ComponentType>()) == 1;
	}

	template<typename ComponentType>
	void addComponent() {
		static_assert(std::is_base_of<Component, ComponentType>::value);
		assert(!hasComponent<ComponentType>());

		components[getComponentHashCode<ComponentType>()] = ComponentType();
		getComponent<ComponentType>().entity = this;
		getComponent<ComponentType>().init();
	}

	template<typename ComponentType>
	void removeComponent() {
		assert(hasComponent<ComponentType>());

		components.erase(getComponentHashCode<ComponentType>());
	}

	template<typename ComponentType>
	ComponentType& getComponent() {
		assert(hasComponent<ComponentType>());

		return std::any_cast<ComponentType&>(components[getComponentHashCode<ComponentType>()]);
	}

	template<typename ComponentType>
	std::size_t getComponentHashCode() const {
		return typeid(ComponentType).hash_code();
	}


	bool hasEntity(const std::string& name);

	void addEntity(const std::string& name);

	void deleteEntity(const std::string& name);

	Entity& getEntity(const std::string& name);

	std::string getName();

private:
	std::unordered_map<std::size_t, std::any> components;

	std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
	std::string name;
};

