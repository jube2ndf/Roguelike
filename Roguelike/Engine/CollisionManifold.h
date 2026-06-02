#pragma once
#include <SFML/System/Vector2.hpp>
namespace GameEngine {
    struct CollisionManifold
    {
        bool collided = false;

        sf::Vector2f normal;// направление выталкивания

        float penetration = 0.f;// глубина пересечения  
    };
}