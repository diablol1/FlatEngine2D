#include "Sprite.hpp"

Sprite::_addToComponentsCreator Sprite::_componentsCreatorAdder;
std::unordered_map<std::string, sf::Texture> Sprite::Textures;

Sprite* Sprite::clone() const {
    return new Sprite(*this);
}

void Sprite::serialize(json& jsonData) const {
    jsonData["texture"] = getTexturePath();
}

void Sprite::deserialize(const json& jsonData) {
    setTexture(jsonData["texture"]);
}

void Entity::drawSprites(const std::shared_ptr<sf::RenderWindow>& window) {
    if (hasComponent<Sprite>()) {
        if (getComponent<Sprite>().isEnabled())
            getComponent<Sprite>().draw(window);
    }

    for (auto& e : entities) {
        if (e.second->active)
            e.second->drawSprites(window);
    }
}

void Sprite::onMessage(const std::string& message, const std::any& value) {
    if (message == "transform changed") {
        const sf::Transform& tmp = std::any_cast<sf::Transformable>(value).getTransform();
        const_cast<sf::Transform&>(sprite.getTransform()) = tmp;
    }
}

void Sprite::draw(const std::shared_ptr<sf::RenderWindow>& window) {
    window->draw(sprite);
}

void Sprite::setTexture(std::string path) {
    if (Textures.count(path)) {
        sprite.setTexture(Textures[path]);
        texturePath = path;
    } else {
        sf::Texture tmp;
        if (tmp.loadFromFile("../game/textures/" + path)) {
            Textures[path] = tmp;
            sprite.setTexture(Textures[path]);
            texturePath = path;
        }
    }
}

std::string Sprite::getTexturePath() const {
    return texturePath;
}