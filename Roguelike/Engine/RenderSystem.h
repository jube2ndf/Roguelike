#pragma once
#include "Scene.h"
#include "ShapeRenderer.h"

namespace GameEngine {
	class RenderSystem
	{
    public:
        void Render(
            sf::RenderWindow& window,
            Scene* scene)
        {
            for (auto& object : scene->GetObjects())
            {
                auto transform =
                    object->GetComponent<TransformComponent>();

                auto renderer =
                    object->GetComponent<ShapeRenderer>();

                if (!transform || !renderer)
                    continue;

                renderer->shape->setPosition(
                    transform->GetWorldPosition());

                renderer->shape->setRotation(
                    sf::degrees(transform->GetWorldRotation()));

                renderer->shape->setScale(
                    transform->GetWorldScale());

                window.draw(*renderer->shape);
            }
        }
	};
}
