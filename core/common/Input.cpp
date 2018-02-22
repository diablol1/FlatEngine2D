#include "Input.hpp"

Input& Input::GetInstance() {
    static Input instance;
    return instance;
}

void Input::registerEvent(const sf::Event& event) {
    sf::Event::EventType type = event.type;

    if(type == sf::Event::KeyPressed) {
        keyAction = Action::Pressed;
        clickedKey = event.key.code;
    }
    else if(type == sf::Event::KeyReleased) {
        keyAction = Action::Released;
        clickedKey = event.key.code;
    }
    else if(type == sf::Event::MouseButtonPressed) {
        buttonAction = Action::Pressed;
        clickedButton = event.mouseButton.button;
    }
    else if(type == sf::Event::MouseButtonReleased) {
        buttonAction = Action::Released;
        clickedButton = event.mouseButton.button;
    }
}

bool Input::getKey(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

bool Input::getKeyDown(sf::Keyboard::Key key) {
    return keyAction == Action::Pressed && clickedKey == key;
}

bool Input::getKeyUp(sf::Keyboard::Key key) {
    return keyAction == Action::Released && clickedKey == key;
}

bool Input::getMouseButton(sf::Mouse::Button button) {
    return sf::Mouse::isButtonPressed(button);
}

bool Input::getMouseButtonDown(sf::Mouse::Button button) {
    return buttonAction == Action::Pressed && clickedButton == button;
}

bool Input::getMouseButtonUp(sf::Mouse::Button button) {
    return buttonAction == Action::Released && clickedButton == button;
}