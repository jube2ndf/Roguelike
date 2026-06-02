#pragma once
#include "Component.h"

namespace GameEngine {
    class ENGINE_API Rigidbody :
        public Component
    {
    public:
        sf::Vector2f velocity{ 0.f,0.f };

        float mass = 1.f;

        bool isKinematic = false;
        Rigidbody(GameObject* owner): Component(owner) {}
    };
}
