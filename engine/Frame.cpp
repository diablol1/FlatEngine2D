#include "Frame.hpp"

Frame::Frame(float startTime, const sf::IntRect& location) : startTime(startTime), location(location) {

}

float Frame::getStartTime() const {
    return startTime;
}

sf::IntRect Frame::getLocation() const {
    return location;
}