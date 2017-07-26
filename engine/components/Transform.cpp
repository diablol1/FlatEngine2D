#include "Transform.hpp"

void Transform::update(float deltaTime) {
    if(entity->getParent() == nullptr) {
        if(toBeUpdated) {
            globalTransform = localTransform;
        }
    }
    else {
        Transform *parentTransform = &entity->getParent()->getComponent<Transform>();

        if(toBeUpdated |= parentTransform->toBeUpdated) {
            globalTransform = parentTransform->globalTransform;
            const_cast<sf::Transform &>(globalTransform.getTransform()).combine(localTransform.getTransform());

            parentTransform->toBeUpdated = false;
            if(entity->getEntities().size() == 0) {
                toBeUpdated = false; //No more children to change transform, so set flag to false
            }

            if(entity->hasComponent<Sprite>())
                entity->sendMessage<Sprite>("transform changed", globalTransform);
        }
    }
}

void Transform::move(const sf::Vector2f &offset) {
    localTransform.move(offset);
    toBeUpdated = true;
}

void Transform::scale(const sf::Vector2f &factors) {
    localTransform.scale(factors);
    toBeUpdated = true;
}

void Transform::rotate(float angle) {
    localTransform.rotate(angle);
    toBeUpdated = true;
}

void Transform::setPosition(const sf::Vector2f &position) {
    localTransform.setPosition(position);
    toBeUpdated = true;
}

void Transform::setScale(const sf::Vector2f &factors) {
    localTransform.setScale(factors);
    toBeUpdated = true;
}

void Transform::setRotation(float angle) {
    localTransform.setRotation(angle);
    toBeUpdated = true;
}

const sf::Vector2f &Transform::getPosition() const {
    return localTransform.getPosition();
}

const sf::Vector2f &Transform::getScale() const {
    return localTransform.getScale();
}

float Transform::getRotation() const {
    return localTransform.getRotation();
}

const sf::Vector2f &Transform::getGlobalPosition() const {
    return globalTransform.getPosition();
}

const sf::Vector2f &Transform::getGlobalScale() const {
    return globalTransform.getScale();
}

float Transform::getGlobalRotation() const {
    return globalTransform.getRotation();
}
