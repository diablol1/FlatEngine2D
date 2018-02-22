#pragma once

#include "ecs/ComponentsCreator.hpp"
#include "common/Logger.hpp"

class Input {
    enum class Action {
        None,
        Pressed,
        Released
    };

public:
    static Input& GetInstance();

    void resetActions() {
        keyAction = Action::None;
        buttonAction = Action::None;
    }

    void registerEvent(const sf::Event& event);

    bool getKey(sf::Keyboard::Key key);
    bool getKeyDown(sf::Keyboard::Key key);
    bool getKeyUp(sf::Keyboard::Key key);

    bool getMouseButton(sf::Mouse::Button button);
    bool getMouseButtonDown(sf::Mouse::Button button);
    bool getMouseButtonUp(sf::Mouse::Button button);

private:
    Input() = default;

    Action keyAction;
    Action buttonAction;

    sf::Keyboard::Key clickedKey;
    sf::Mouse::Button clickedButton;
};