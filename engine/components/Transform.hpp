#pragma once

#include "common/Vector2.hpp"
#include "ecs/Entity.hpp"
#include "ecs/Component.hpp"
#include "components/Camera.hpp"

class Transform : public Component {
public:
    static class _addToComponentsCreator {
    public:
        _addToComponentsCreator() {
            ComponentsCreator::GetInstance().add<Transform>();
        }
    } _componentsCreatorAdder;

    Transform* clone() const override;

    void serialize(json& jsonData) const override;
    void deserialize(const json& jsonData) override;

    void move(const Vector2& offset);
    void scale(const Vector2& factors);
    void rotate(float angle);

    void setPosition(const Vector2& position);
    void setScale(const Vector2& factors);
    void setRotation(float angle);

    Vector2 getPosition() const;
    Vector2 getScale() const;
    float getRotation() const;

    Vector2 getGlobalPosition() const;
    Vector2 getGlobalScale() const;
    float getGlobalRotation() const;

private:
    sf::Transformable globalTransform;
    sf::Transformable localTransform;

    bool toBeUpdated = true;

    void update(float deltaTime) override;
};