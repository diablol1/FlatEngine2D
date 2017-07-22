#pragma once

#include <ecs/Entity.hpp>
#include <ecs/Component.hpp>

class Transform : public Component, public sf::Transformable {
public:
    void update(float deltaTime) override;

    sf::Vector2f getGlobalPosition() const;
    sf::Vector2f getGlobalScale() const;
    float getGlobalRotation() const;

private:
    sf::Vector2f globalPosition;
    sf::Vector2f globalScale;
    float globalRotation;
};