#pragma once

#include <unordered_map>

#include "ecs/ComponentsCreator.h"
#include "ecs/Component.hpp"
#include "components/Transform.hpp"

class Sprite : public Component {
    friend class Entity;
public:
    static class _addToComponentsCreator {
    public:
        _addToComponentsCreator() {
            ComponentsCreator::GetInstance().add<Sprite>();
        }
    } _componentsCreatorAdder;

    Sprite* clone() const override;

    void serialize(json& jsonData) const override;
    void deserialize(const json& jsonData) override;

    void setTexture(std::string path);
    std::string getTexturePath() const;
private:

    static std::unordered_map<std::string, sf::Texture> Textures;
    sf::Sprite sprite;
    std::string texturePath;

    void onMessage(const std::string& message, const std::any& value) override;

    void draw(const std::shared_ptr<sf::RenderWindow>& window);
};