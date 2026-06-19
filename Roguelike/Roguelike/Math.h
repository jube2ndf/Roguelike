#pragma once
#include <SFML/System/Vector2.hpp>
class Math
{
  public:
    static float Length(const sf::Vector2f& v);

    static sf::Vector2f Normalize(sf::Vector2f v);
};
