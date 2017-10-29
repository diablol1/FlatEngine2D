#include "Camera.hpp"

Camera::_addToComponentsCreator Camera::_componentsCreatorAdder;
std::vector<Camera*> Camera::AllCameras;
std::shared_ptr<sf::RenderWindow> Camera::window;

Camera* Camera::clone() const {
    return new Camera(*this);
}

void Camera::init() {
    view.setSize(sf::Vector2f(window->getSize()));

    AllCameras.push_back(this);
}

void Camera::update(float deltaTime) {
    window->setView(view);
}

void Camera::onEnable() {
    bool anyDisabled = false;
    for (auto& c : AllCameras) {
        if (c != this && c->isEnabled()) {
            c->setEnabled(false);
            anyDisabled = true;
            break;
        }
    }
    if (anyDisabled)
        Logger::GetInstance().log(Logger::MessageType::Warning,
                                  "There were 2 cameras enabled. The older camera has been disabled");
}

void Camera::serialize(json& jsonData) const {
    jsonData["size"]["x"] = view.getSize().x;
    jsonData["size"]["y"] = view.getSize().y;
}

void Camera::deserialize(const json& jsonData) {
    view.setSize(jsonData["size"]["x"],
                 jsonData["size"]["y"]);
}

void Camera::onMessage(const std::string& message, const std::any& value) {
    if (message == "transform changed") {
        const sf::Transformable& tmp = std::any_cast<sf::Transformable>(value);
        view.setCenter(tmp.getPosition());
        view.setRotation(tmp.getRotation());
    }
}
void Camera::zoom(float factor) {
    view.zoom(factor);
}