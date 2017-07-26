#pragma once

#include <unordered_map>
#include <iostream>

#include <ecs/Component.hpp>

#include <components/Transform.hpp>

class Sprite : public Component {
    friend class Entity;
public:
    Sprite(const std::string& texturePath);

    void setTexture(std::string path);
private:
    static std::unordered_map<std::string, sf::Texture> Textures;
    sf::Sprite sprite;

    void onMessage(const std::string &message, const std::any &value) override;

    void draw(sf::RenderWindow& window);
};