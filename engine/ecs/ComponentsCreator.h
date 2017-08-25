#pragma once

#include <unordered_map>

#include <utility.h>

#include "Component.hpp"

class ComponentsCreator {
public:
    static ComponentsCreator& GetInstance();

    template<typename ComponentType>
    void add() {
        static_assert(std::is_base_of<Component, ComponentType>::value);

        components[utility::getClassName<ComponentType>()] = std::make_shared<ComponentType>(ComponentType());
    }

    std::shared_ptr<Component> create(const std::string& componentName);

private:
    std::unordered_map<std::string, std::shared_ptr<Component>> components;

    ComponentsCreator() {}
};