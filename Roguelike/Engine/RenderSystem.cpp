#include "pch.h"
#include "RenderSystem.h"
#include "Collider.h"
#include "GameObject.h"
#include "Scene.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "Logger.h"

void GameEngine::RenderSystem::Render(sf::RenderWindow &window, Scene *scene) {
  window.clear();
  window.setView(scene->GetCamera().GetView());
  
  auto center = window.getView().getCenter();
  auto size = window.getView().getSize();

  float margin = 200.f;

  std::vector<GameObject*> renderQueue;

  sf::FloatRect viewRect(
      {center.x - size.x * 0.5f - margin, center.y - size.y * 0.5f - margin},
      {size.x + margin * 2.f, size.y + margin * 2.f});

  for (auto& object : scene->GetObjects())
  {
      auto* spriteRenderer =
          object->GetComponent<SpriteRenderer>();

      if (!spriteRenderer)
          continue;

      if (!viewRect.findIntersection(
              spriteRenderer->GetSprite().getGlobalBounds()))
      {
          //LOG_INFO("Render", "Object not render: " + std::to_string(reinterpret_cast<uintptr_t>(object.get())));
          continue;
      }
      renderQueue.push_back(object.get());
  }

  std::sort(
      renderQueue.begin(),
      renderQueue.end(),
      [](GameObject* a, GameObject* b) {
          auto* sa =
              a->GetComponent<SpriteRenderer>();

          auto* sb =
              b->GetComponent<SpriteRenderer>();

          return sa->sortingLayer <
                 sb->sortingLayer;
      });

  for (auto& object : renderQueue)
  {
    if (auto spriteRenderer = object->GetComponent<SpriteRenderer>()) {
      if (!viewRect.findIntersection(spriteRenderer->GetSprite().getGlobalBounds()))
        continue;
    }
    auto transform = object->GetComponent<TransformComponent>();

    if (!transform)
      continue;

    // ===== SHAPES =====
    if (auto shapeRenderer = object->GetComponent<ShapeRenderer>()) {
      shapeRenderer->shape->setPosition(transform->GetWorldPosition());

      shapeRenderer->shape->setRotation(
          sf::degrees(transform->GetWorldRotation()));

      shapeRenderer->shape->setScale(transform->GetWorldScale());

      window.draw(*shapeRenderer->shape);
    }

    // ===== SPRITES =====
    if (auto spriteRenderer = object->GetComponent<SpriteRenderer>()) {
      auto &sprite = spriteRenderer->GetSprite();

      sprite.setPosition(transform->GetWorldPosition());

      sprite.setRotation(sf::degrees(transform->GetWorldRotation()));

      sf::Vector2f worldSize;

      // ===== 1. ПЫТАЕМСЯ БРАТЬ РАЗМЕР ИЗ COLLIDER =====
      if (auto collider = object->GetComponent<Collider>()) {
        worldSize = collider->GetSize();
      }
      // ===== 2. ИНАЧЕ FALLBACK НА TRANSFORM =====
      else {
        worldSize = transform->GetWorldScale();
      }

      auto texSize = sprite.getTexture().getSize();

      sprite.setScale({worldSize.x / static_cast<float>(texSize.x),
                       worldSize.y / static_cast<float>(texSize.y)});

      window.draw(sprite);
    }
  }

  window.display();
}
