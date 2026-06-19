#pragma once
#include "ProjectileComponent.h"
#include <GameObject.h>
namespace Roguelike
{
class FastSwordProjectile
{
  public:
    static void AddFastSwordProjectile(GameEngine::GameObject* owner);
    static void RemoveFastSwordProjectile(GameEngine::GameObject* owner);
};
} // namespace Roguelike
