#include "Vector2.hpp"

Vector2 Vector2::operator+(const Vector2& v) const {
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const {
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(float factor) const {
    return Vector2(x * factor, y * factor);
}

Vector2 Vector2::operator/(float factor) const {
    return Vector2(x / factor, y / factor);
}

bool Vector2::operator==(const Vector2& v) const {
    return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v) const {
    return x != v.x || y != v.y;
}

sf::Vector2f Vector2::getSfmlVector() const {
    return sf::Vector2f(x, y);
}