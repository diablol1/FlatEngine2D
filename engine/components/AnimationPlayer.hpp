#pragma once

#include "ecs/Component.hpp"
#include "ecs/ComponentsCreator.hpp"
#include "components/Sprite.hpp"
#include "Animation.hpp"

class AnimationPlayer : public Component {
public:
    static class _addToComponentsCreator {
    public:
        _addToComponentsCreator() {
            ComponentsCreator::GetInstance().add<AnimationPlayer>();
        }
    } _componentsCreatorAdder;

    Component* clone() const override;
    void serialize(json& jsonData) const override;
    void deserialize(const json& jsonData) override;

    void update(float deltaTime) override;

    void setSpriteSheet(const std::string& filename);
    void play(const std::string& filename);
    void stop();
private:
    static std::unordered_map<std::string, std::shared_ptr<Animation>> Animations;
    bool playing = false;
    std::string currentAnimation;
    int currentFrame = 0;
    sf::Clock timeSinceAnimationStart;

    void loadAnimationIfNotLoaded(const std::string& filename);
};