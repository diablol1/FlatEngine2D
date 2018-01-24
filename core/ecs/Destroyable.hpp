#pragma once

#include <SFML/System.hpp>

class Destroyable {
public:
    void destroy(float timeToDelay = 0.0f);
    bool isReadyToDestroy() const;
private:
    bool toBeDestroyed = false;
    float timeToDelay;
    sf::Clock elapsedTime;

    bool hasToBeDestroyed() const;
    bool hasTimeToDelayElapsed() const;
};