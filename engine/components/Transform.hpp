#pragma once

#include <ecs/Entity.hpp>
#include <ecs/Component.hpp>

class Transform : public Component {
public:
    void move(const sf::Vector2f& offset);
    void scale(const sf::Vector2f& factors);
    void rotate(float angle);

    void setPosition(const sf::Vector2f &position);
    void setScale(const sf::Vector2f &factors);
    void setRotation(float angle);

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getScale() const;
    float getRotation() const;

    const sf::Vector2f& getGlobalPosition() const;
    const sf::Vector2f& getGlobalScale() const;
    float getGlobalRotation() const;

private:
    sf::Transformable globalTransform;
    sf::Transformable localTransform;

    bool toBeUpdated = true;

    void update(float deltaTime) override;
};