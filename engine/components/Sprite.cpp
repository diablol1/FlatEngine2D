#include "Sprite.hpp"

std::unordered_map<std::string, sf::Texture> Sprite::Textures;

Sprite::Sprite(const std::string& texturePath) {
    setTexture(texturePath);
}

void Sprite::update(float deltaTime) {
    Transform* transform = &entity->getComponent<Transform>();

    sprite.setPosition(transform->getGlobalPosition());
    sprite.setRotation(transform->getGlobalRotation());
    sprite.setScale(transform->getGlobalScale());
}

void Sprite::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Sprite::setTexture(std::string path) {
    path = "../game/textures/" + path; //Making path relevant to game/textures/

    if(Textures.count(path))
        sprite.setTexture(Textures[path]);
    else {
        sf::Texture tmp;
        if(tmp.loadFromFile(path)) {
            Textures[path] = tmp;
            sprite.setTexture(Textures[path]);
        }
    }
}