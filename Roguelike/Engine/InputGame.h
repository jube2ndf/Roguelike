#pragma once
#include "EngineAPI.h"
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
class ENGINE_API InputGame
{
  public:
    inline static sf::Vector2f mouseWorldPosition;
};
}