#include "Entity.hpp"

std::unordered_set<std::string> Entity::Tags;
std::unordered_map<std::string, Entities> Entity::EntitiesGroupedByTags;
Entity* Entity::Root;

void Entity::LoadTagsFromFile(const std::string& filename) {
    if (!Entity::Tags.empty()) {
        Logger::GetInstance().log(Logger::MessageType::Error, "Tags already exist. They can't be loaded");
        return;
    }

    std::ifstream file(filename);
    if (!file.is_open() || utility::isFileEmpty(file)) {
        Logger::GetInstance().log(Logger::MessageType::Error,
                                  "Tags couldn't be loaded from file \"" + filename
                                      + "\". Make sure it exists and isn't empty");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        Tags.insert(line);
    }
}

Entities& Entity::GetEntitiesByTag(const std::string& tag) {
    assert(Entity::Tags.count(tag));
    return EntitiesGroupedByTags[tag];
}

Entity& Entity::GetRoot() {
    if (Root == nullptr) {
        Logger::GetInstance().log(Logger::MessageType::Error, "There is no created entity. Root is nullptr");
    }
    return *Root;
}

Entity::Entity(const std::string& name, const std::string& tag, Entity* parent) {
    if (parent == nullptr)
        Root = this;

    setName(name);

    auto ptr = std::shared_ptr < Entity
        > (this, [](Entity*) {}); //Allow to call setTag which use shared_from_this() from constructor
    setTag(tag);

    this->parent = parent;

    addComponent<Transform>();
}

void Entity::saveToFile(const std::string& filename) {
    json jsonData;
    serialize(jsonData);

    std::ofstream file("../game/scenes/" + filename);
    file << jsonData.dump(2);
    file.close();
}

void Entity::loadFromFile(const std::string& filename) {
    std::ifstream file("../game/scenes/" + filename);

    if (!file.is_open()) {
        Logger::GetInstance().log(Logger::MessageType::Error, "Entity \"" + filename + "\" couldn't be loaded");
        return;
    }

    entities.clear();
    components.clear();

    json jsonData;
    file >> jsonData;
    file.close();

    deserialize(jsonData);
}

void Entity::serialize(json& jsonData) const {
    jsonData["name"] = name;
    jsonData["tag"] = tag;
    jsonData["active"] = active;

    for (const auto& c : components) {
        std::string componentName = utility::getClassName(*c.second);

        c.second->serialize(jsonData["components"][componentName]);
        jsonData["components"][componentName]["enabled"] = c.second->isEnabled();
    }

    for (const auto& e : entities) {
        e.second->serialize(jsonData["entities"][e.second->getName()]);
    }
}

void Entity::deserialize(const json& jsonData) {
    setName(jsonData["name"]);
    setTag(jsonData["tag"]);
    active = jsonData["active"];

    if (jsonData.count("components")) {
        for (auto it = jsonData["components"].begin(); it != jsonData["components"].end(); ++it) {
            std::string componentName = it.key();
            auto componentFields = it.value();

            std::shared_ptr < Component > component = ComponentsCreator::GetInstance().create(componentName);

            component->entity = this;
            component->init();
            component->deserialize(componentFields);
            component->setEnabled(componentFields["enabled"]);

            components[utility::getClassHashCode(*component)] = component;
        }
    }

    if (jsonData.count("entities")) {
        for (const auto& j : jsonData["entities"]) {
            addEntity("tmpName", "Default");
            getEntity("tmpName").deserialize(j);
        }
    }
}

void Entity::update(float deltaTime) {
    checkForDestroying();

    for (auto& c : components) {
        if (c.second->isEnabled())
            c.second->update(deltaTime);
    }

    for (auto& e : entities) {
        if (e.second->active)
            e.second->update(deltaTime);
    }
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

void Entity::checkForDestroying() {
    for (auto it = entities.begin(); it != entities.end();) {
        if (it->second->isReadyToDestroy())
            it = entities.erase(it);
        else
            ++it;
    }

    for (auto it = components.begin(); it != components.end();) {
        if (it->second->isReadyToDestroy())
            it = components.erase(it);
        else
            ++it;
    }
}

bool Entity::hasEntity(const std::string& name) {
    return entities.count(name) == 1;
}

void Entity::addEntity(const std::string& name, const std::string& tag) {
    if (hasEntity(name)) {
        Logger::GetInstance().log(Logger::MessageType::Error,
                                  "Entity \"" + name + "\" already exists. It can't be created");
        return;
    }

    entities[name] = std::make_unique<Entity>(name, tag, this);
}

Entity& Entity::getEntity(const std::string& name) {
    if (!hasEntity(name))
        Logger::GetInstance().log(Logger::MessageType::Error,
                                  "Entity \"" + name + "\" doesn't exist. It can't be returned");

    return *entities[name];
}

void Entity::setName(const std::string& name) {
    if (this->name != name) {
        if (parent == nullptr || this->name == "")
            this->name = name;
        else {
            std::string oldName = this->name;
            this->name = name;

            parent->entities[name] = parent->entities[oldName];
            parent->entities.erase(oldName);
        }
    }
}

std::string Entity::getName() const {
    return name;
}

std::string Entity::getTag() const {
    return tag;
}

void Entity::setTag(const std::string& tag) {
    if (!Tags.count(tag)) {
        Logger::GetInstance().log(Logger::MessageType::Error,
                                  "Entity \"" + name + '"' + " can't set non-created tag " + '"' + tag + '"');
        return; 
    }

    std::string oldTag = this->tag;
    this->tag = tag;

    Entity::EntitiesGroupedByTags[tag].insert(shared_from_this());

    if (oldTag != "")
        Entity::EntitiesGroupedByTags[oldTag].erase(shared_from_this());
}

Entity* Entity::getParent() {
    return parent;
}

std::unordered_map<std::string, std::shared_ptr<Entity>>& Entity::getEntities() {
    return entities;
}