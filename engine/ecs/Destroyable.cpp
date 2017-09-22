#include "Destroyable.hpp"

void Destroyable::destroy(float timeToDelay) {
    toBeDestroyed = true;
    elapsedTime.restart();
    this->timeToDelay = timeToDelay;
}

bool Destroyable::hasToBeDestroyed() const {
    return toBeDestroyed;
}

bool Destroyable::hasTimeToDelayElapsed() const {
    return elapsedTime.getElapsedTime().asSeconds() >= timeToDelay;
}

bool Destroyable::isReadyToDestroy() const {
    return hasToBeDestroyed() && hasTimeToDelayElapsed();
}
