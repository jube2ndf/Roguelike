#pragma once
#include "Collider.h"
#include "CircleCollider.h"
#include <SFML/System/Vector2.hpp>

namespace GameEngine {
    class ENGINE_API BoxCollider : public Collider
    {
    public:
        sf::Vector2f size{ 50.f, 50.f };

        BoxCollider(GameObject* owner)
            : Collider(owner)
        {}

        sf::Vector2f GetSize() const override {
            return size;
        }

        float GetRadius() override
        {
            auto half = GetHalfSize();

            return std::sqrt(
                half.x * half.x +
                half.y * half.y);
        }

        sf::Vector2f GetHalfSize() const {
            return { size.x / 2.f, size.y / 2.f };
        }

        std::vector<sf::Vector2f> GetWorldVertices() const;

    };
}