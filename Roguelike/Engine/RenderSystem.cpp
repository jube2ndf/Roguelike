#include "pch.h"
#include "RenderSystem.h"

#include "Scene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ShapeRenderer.h"

void GameEngine::RenderSystem::Render(sf::RenderWindow& window, Scene* scene)
{
    window.clear();
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
    window.display();
}
