#include "pch.h"
#include "RenderSystem.h"
#include "Collider.h"
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
            auto& sprite = spriteRenderer->GetSprite();

            sprite.setPosition(transform->GetWorldPosition());

            sprite.setRotation(sf::degrees(transform->GetWorldRotation()));

            sf::Vector2f worldSize;

            // ===== 1. ПЫТАЕМСЯ БРАТЬ РАЗМЕР ИЗ COLLIDER =====
            if (auto collider = object->GetComponent<Collider>())
            {
                worldSize = collider->GetSize();
            }
            // ===== 2. ИНАЧЕ FALLBACK НА TRANSFORM =====
            else
            {
                worldSize = transform->GetWorldScale();
            }

            auto texSize = sprite.getTexture().getSize();

            sprite.setScale(
                { worldSize.x / static_cast<float>(texSize.x),
                worldSize.y / static_cast<float>(texSize.y) }
            );

            window.draw(sprite);
        }
    }

    window.display();
}
