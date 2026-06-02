#include "pch.h"
#include "RenderSystem.h"

#include "Scene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"

void GameEngine::RenderSystem::Render(sf::RenderWindow& window, Scene* scene)
{
    window.clear();

    for (auto& object : scene->GetObjects())
    {
        auto transform =
            object->GetComponent<TransformComponent>();

        if (!transform)
            continue;

        // ===== SHAPES =====
        if (auto shapeRenderer =
            object->GetComponent<ShapeRenderer>())
        {
            shapeRenderer->shape->setPosition(
                transform->GetWorldPosition());

            shapeRenderer->shape->setRotation(
                sf::degrees(transform->GetWorldRotation()));

            shapeRenderer->shape->setScale(
                transform->GetWorldScale());

            window.draw(*shapeRenderer->shape);
        }

        // ===== SPRITES =====
        if (auto spriteRenderer =
            object->GetComponent<SpriteRenderer>())
        {
            spriteRenderer->GetSprite().setPosition(
                transform->GetWorldPosition());

            spriteRenderer->GetSprite().setRotation(
                sf::degrees(transform->GetWorldRotation()));

            spriteRenderer->GetSprite().setScale(
                transform->GetWorldScale());

            window.draw(spriteRenderer->GetSprite());
        }
    }

    window.display();
}
