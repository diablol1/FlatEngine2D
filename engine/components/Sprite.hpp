#pragma once

#include <unordered_map>
#include <iostream>

#include <ecs/Component.hpp>

#include <components/Transform.hpp>

class Sprite : public Component {
public:
    Sprite(const std::string& texturePath);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window);

    void setTexture(std::string path);
private:
    static std::unordered_map<std::string, sf::Texture> Textures;

    sf::Sprite sprite;
};
