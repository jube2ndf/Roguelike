#pragma once
#include "Collider.h"
#include <SFML/System/Vector2.hpp>

namespace GameEngine {
    class ENGINE_API BoxCollider : public Collider
    {
    public:
        sf::Vector2f size{ 50.f, 50.f };

        BoxCollider(GameObject* owner)
            : Collider(owner)
        {}
    };
}