#pragma once
#include "ProjectileComponent.h"
#include <GameObject.h>
#include "WeaponType.h"
namespace Roguelike
{
class SwordProjectile
{
  public:
    static void AddSwordProjectile(GameEngine::GameObject* owner, WeaponType type);
    static void RemoveSwordProjectile(GameEngine::GameObject* owner, WeaponType type);
};
} // namespace Roguelike
