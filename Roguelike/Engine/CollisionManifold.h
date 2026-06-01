#pragma once
#include <SFML/System/Vector2.hpp>
namespace GameEngine {
    struct CollisionManifold
    {
        sf::Vector2f normal;   // направление выталкивания
        float penetration;     // глубина пересечения
    };
}