#pragma once

#include <SFML/System.hpp>

class Vector2 {
public:
    float x, y;

    Vector2() = default;

    Vector2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    template<typename vectorType>
    Vector2(const sf::Vector2<vectorType> sfmlVector) {
        x = sfmlVector.x;
        y = sfmlVector.y;
    }

    Vector2 operator+(const Vector2& v) const;

    Vector2 operator-(const Vector2& v) const;

    Vector2 operator*(float factor) const;

    Vector2 operator/(float factor) const;

    bool operator==(const Vector2& v) const;
    bool operator!=(const Vector2& v) const;

    sf::Vector2f getSfmlVector() const;
};