#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Component.h"

namespace GameEngine {
    class ShapeRenderer : public Component
    {
    public:
        std::unique_ptr<sf::Shape> shape;

        ShapeRenderer(GameObject* owner)
            : Component(owner)
        {
            auto circle =
                std::make_unique<sf::CircleShape>();
            circle->setRadius(50.f);
            circle->setFillColor(sf::Color::Red);
            shape = std::move(circle);
        }
    };
}