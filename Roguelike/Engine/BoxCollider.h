#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>

namespace GameEngine {
    class BoxCollider : public Component
    {
    public:
        sf::Vector2f size{ 50.f, 50.f };

        BoxCollider(GameObject* owner)
            : Component(owner)
        {}
    };
}