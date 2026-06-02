#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace GameEngine {

    inline float Dot(const sf::Vector2f& a, const sf::Vector2f& b) {
        return a.x * b.x + a.y * b.y;
    }

    inline float LengthSq(const sf::Vector2f& v) {
        return v.x * v.x + v.y * v.y;
    }

    inline float Length(const sf::Vector2f& v) {
        return std::sqrt(LengthSq(v));
    }

    inline sf::Vector2f Normalize(const sf::Vector2f& v) {
        float len = Length(v);
        if (len > 0)
            return { v.x / len, v.y / len };
        return { 0, 0 };
    }

    inline float ToRadians(float degrees) {
        return degrees * 3.14159265358979f / 180.f;
    }

    inline float ToDegrees(float radians) {
        return radians * 180.f / 3.14159265358979f;
    }

    inline sf::Vector2f Rotate(const sf::Vector2f& v, float angleDegrees) {
        float rad = ToRadians(angleDegrees);
        float cos = std::cos(rad);
        float sin = std::sin(rad);
        return {
            v.x * cos - v.y * sin,
            v.x * sin + v.y * cos
        };
    }
}