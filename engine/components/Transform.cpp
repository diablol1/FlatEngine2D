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
    setPosition(Vector2(jsonData["position"]["x"],
                             jsonData["position"]["y"]));

    setScale(Vector2(jsonData["scale"]["x"],
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
            //TODO: Find out better solution for this. Transform shouldn't know too much about other components
            if (entity->hasComponent<Sprite>())
                entity->sendMessage<Sprite>("transform changed", globalTransform);
            if (entity->hasComponent<Camera>())
                entity->sendMessage<Camera>("transform changed", globalTransform);
        }
    }
}

void Transform::move(const Vector2& offset) {
    localTransform.move(offset.getSfmlVector());
    toBeUpdated = true;
}

void Transform::scale(const Vector2& factors) {
    localTransform.scale(factors.getSfmlVector());
    toBeUpdated = true;
}

void Transform::rotate(float angle) {
    localTransform.rotate(angle);
    toBeUpdated = true;
}

void Transform::setPosition(const Vector2& position) {
    localTransform.setPosition(position.getSfmlVector());
    toBeUpdated = true;
}

void Transform::setScale(const Vector2& factors) {
    localTransform.setScale(factors.getSfmlVector());
    toBeUpdated = true;
}

void Transform::setRotation(float angle) {
    localTransform.setRotation(angle);
    toBeUpdated = true;
}

Vector2 Transform::getPosition() const {
    return localTransform.getPosition();
}

Vector2 Transform::getScale() const {
    return localTransform.getScale();
}

float Transform::getRotation() const {
    return localTransform.getRotation();
}

Vector2 Transform::getGlobalPosition() const {
    return globalTransform.getPosition();
}

Vector2 Transform::getGlobalScale() const {
    return globalTransform.getScale();
}

float Transform::getGlobalRotation() const {
    return globalTransform.getRotation();
}