#include "Transform.hpp"

Transform::_addToComponentsCreator Transform::_componentsCreatorAdder;

Transform* Transform::clone() const {
    return new Transform(*this);
}

void Transform::serialize(json& jsonData) const {
    jsonData["position"]["x"] = getPosition().x;
    jsonData["position"]["y"] = getPosition().y;

    jsonData["scale"]["x"] = getScale().x;
    jsonData["scale"]["y"] = getScale().y;

    jsonData["rotation"] = getRotation();
}

void Transform::deserialize(const json& jsonData) {
    setPosition(sf::Vector2f(jsonData["position"]["x"],
                             jsonData["position"]["y"]));

    setScale(sf::Vector2f(jsonData["scale"]["x"],
                          jsonData["scale"]["y"]));

    setRotation(jsonData["rotation"]);
}

void Transform::update(float deltaTime) {
    if (entity->getParent() == nullptr) {
        if (toBeUpdated) {
            globalTransform = localTransform;
        }
    } else {
        Transform* parentTransform = &entity->getParent()->getComponent<Transform>();

        if (toBeUpdated |= parentTransform->toBeUpdated) {
            globalTransform = parentTransform->globalTransform;

            globalTransform.move(localTransform.getPosition());
            globalTransform.rotate(localTransform.getRotation());
            globalTransform.scale(localTransform.getScale());

            parentTransform->toBeUpdated = false;
            if (entity->getEntities().size() == 0) {
                toBeUpdated = false; //No more children to change transform, so set flag to false
            }

            if (entity->hasComponent<Sprite>())
                entity->sendMessage<Sprite>("transform changed", globalTransform);
        }
    }
}

void Transform::move(const sf::Vector2f& offset) {
    localTransform.move(offset);
    toBeUpdated = true;
}

void Transform::scale(const sf::Vector2f& factors) {
    localTransform.scale(factors);
    toBeUpdated = true;
}

void Transform::rotate(float angle) {
    localTransform.rotate(angle);
    toBeUpdated = true;
}

void Transform::setPosition(const sf::Vector2f& position) {
    localTransform.setPosition(position);
    toBeUpdated = true;
}

void Transform::setScale(const sf::Vector2f& factors) {
    localTransform.setScale(factors);
    toBeUpdated = true;
}

void Transform::setRotation(float angle) {
    localTransform.setRotation(angle);
    toBeUpdated = true;
}

const sf::Vector2f& Transform::getPosition() const {
    return localTransform.getPosition();
}

const sf::Vector2f& Transform::getScale() const {
    return localTransform.getScale();
}

float Transform::getRotation() const {
    return localTransform.getRotation();
}

const sf::Vector2f& Transform::getGlobalPosition() const {
    return globalTransform.getPosition();
}

const sf::Vector2f& Transform::getGlobalScale() const {
    return globalTransform.getScale();
}

float Transform::getGlobalRotation() const {
    return globalTransform.getRotation();
}
