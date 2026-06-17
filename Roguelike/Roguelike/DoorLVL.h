#pragma once
#include <GameObject.h>
#include <Scene.h>
#include <SpriteRenderer.h>
#include <TextureManager.h>
#include "DoorTrigget.h"
#include "CollisionLayers.h"
#include <string>
namespace Roguelike
{
class Door
{
  public:
    static GameEngine::GameObject* Create(GameEngine::Scene& scene, std::string path2Scene, sf::Vector2f pos, sf::Vector2f size)
    {
        auto exit = scene.CreateObject();

        auto tr =
            exit->GetComponent<GameEngine::TransformComponent>();

        tr->SetWorldPosition(pos);

        auto col =
            exit->AddComponent<GameEngine::SpriteRenderer>(
                GameEngine::TextureManager::load("./Resources/Textures/door.png")
            );

        auto collider =
            exit->AddComponent<DoorTrigget>(path2Scene);
        collider->size = size;
        collider->layer = CollisionLayers::Door;
        collider->mask =
            CollisionLayers::PlayerBody;
        return exit;
    }
};
} // namespace Roguelike