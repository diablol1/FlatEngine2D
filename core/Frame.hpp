#pragma once

#include <SFML/Graphics.hpp>

class Frame {
public:
    Frame(float startTime, const sf::IntRect& location);

    float getStartTime() const;
    sf::IntRect getLocation() const;
private:
    float startTime;
    sf::IntRect location;
};