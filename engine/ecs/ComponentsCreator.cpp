#include "ComponentsCreator.h"

ComponentsCreator &ComponentsCreator::GetInstance() {
    static ComponentsCreator instance;
    return instance;
}

std::shared_ptr<Component> ComponentsCreator::create(const std::string& componentName) {
    return std::shared_ptr<Component>(components[componentName]->clone());
}