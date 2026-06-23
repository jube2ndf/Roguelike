#pragma once
#include <Scene.h>
#include <GameObject.h>
#include "IItem.h"
#include "InventoryItemObject.h"
#include <SpriteRenderer.h>
#include <TextureManager.h>
#include "HealthPotion.h"


namespace Roguelike
{
class Potion
{
public:
    static void CreateHeatlPotion(GameEngine::Scene& scene, sf::Vector2f pos)
    {
        GameEngine::GameObject* owner = scene.CreateObject();
        CreateSharedData(owner, pos);
        std::shared_ptr<IItem> item = std::make_shared<HealthPotion>(50);
        CreateUniqueData(owner, item, "./Resources/Textures/HealthPotion.png", {8,8});
    }

private:
    static void CreateSharedData(
      GameEngine::GameObject* owner,
      sf::Vector2f pos
  )
  {
      auto tr =
          owner->GetComponent<GameEngine::TransformComponent>();
      tr->SetWorldPosition(pos);
  }

    static void CreateUniqueData(
        GameEngine::GameObject* owner, 
        std::shared_ptr<IItem> item, 
        std::string texturePath,
        sf::Vector2f size)
    {
        auto inventory = owner->AddComponent<InventoryItemObject>(item);

        auto sprite = owner->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load(texturePath));
        sprite->sortingLayer = 8;
        inventory->size = size;
    }
};
} // namespace Roguelike