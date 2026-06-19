#include "Math.h"

float Math::Length(const sf::Vector2f& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f Math::Normalize(sf::Vector2f v)
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);

    if (length == 0.f)
        return {0.f, 0.f};

    return {v.x / length, v.y / length};
}
