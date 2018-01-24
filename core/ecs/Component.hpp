#pragma once

#include <SFML/Graphics.hpp>

#include <experimental/any>

#include "ecs/Destroyable.hpp"
#include "ecs/Serializable.hpp"

class Entity;

/*NOTE:
 * Component which uses another component has to be added as the second one
 * E.g. Adding Collider after Position, because Collider needs Position
 * Scripts should be added after normal components
*/

class Component : public Destroyable, public Serializable {
    friend class Entity;
public:
    virtual Component* clone() const = 0;

    void setEnabled(bool flag);
    bool isEnabled() const;
protected:
    Entity* entity;

    virtual void init() {}
    virtual void update(float deltaTime) {}
    virtual void processEvent(const sf::Event& event) {}

    virtual void onEnable() {}
    virtual void onDisable() {}

    virtual void onMessage(const std::string& message, const std::experimental::any& value) {}
private:
    bool enabled = true;
};