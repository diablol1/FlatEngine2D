#include "Sprite.hpp"

std::unordered_map<std::string, sf::Texture> Sprite::Textures;

Sprite::Sprite(const std::string& texturePath) {
    setTexture(texturePath);
}

void Entity::drawSprites(sf::RenderWindow& window) {
    if(hasComponent<Sprite>())
        getComponent<Sprite>().draw(window);

    for(auto& e : entities) {
        e.second->drawSprites(window);
    }
}

void Sprite::onMessage(const std::string &message, const std::any &value) {
    if(message == "transform changed") {
        const sf::Transform& tmp = std::any_cast<sf::Transformable>(value).getTransform();
        const_cast<sf::Transform&>(sprite.getTransform()) = tmp;
    }
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