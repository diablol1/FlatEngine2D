    #pragma once

#include <SFML/Graphics.hpp>

#include "common/Logger.hpp"
#include "ecs/ComponentsCreator.hpp"
#include "ecs/Component.hpp"
#include "components/Transform.hpp"

class Camera : public Component {
public:
    static class _addToComponentsCreator {
    public:
        _addToComponentsCreator() {
            ComponentsCreator::GetInstance().add<Camera>();
        }
    } _componentsCreatorAdder;

    static std::shared_ptr<sf::RenderWindow> window;

    Camera* clone() const override;

    void init() override;

    void serialize(json& jsonData) const override;
    void deserialize(const json& jsonData) override;

    void onMessage(const std::string& message, const std::experimental::any& value) override;

    void zoom(float factor);
private:
    static std::vector<Camera*> AllCameras;

    sf::View view;

    void update(float deltaTime) override;

    void onEnable();
};