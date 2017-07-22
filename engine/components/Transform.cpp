#include "Transform.hpp"

void Transform::update(float deltaTime) {
    if(entity->getParent() == nullptr) {
        globalPosition = getPosition();
        globalRotation = getRotation();
        globalScale = getScale();
    }
    else {
        Transform* parentTransform = &entity->getParent()->getComponent<Transform>();

        globalPosition = parentTransform->getGlobalPosition() + getPosition();
        globalRotation = parentTransform->getGlobalRotation() + getRotation();
        globalScale = sf::Vector2f(parentTransform->getGlobalScale().x * getScale().x,
                                   parentTransform->getGlobalScale().y * getScale().y);
    }
}

sf::Vector2f Transform::getGlobalPosition() const {
    return globalPosition;
}

sf::Vector2f Transform::getGlobalScale() const {
    return globalScale;
}

float Transform::getGlobalRotation() const {
    return globalRotation;
}