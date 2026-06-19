#pragma once
#include <Scene.h>
#include "SpawnEvent.h"
#include <unordered_map>
#include "CreateWeapon.h"
#include "WeaponType.h"
namespace Roguelike
{
class WeaponFactory
{
  public:
    static std::unordered_map<WeaponType, float> culDown;
    static void Create(GameEngine::Scene& scene, CreateWeapon data);

  private:
    static void CreaetSword(GameEngine::Scene& scene, 
        CreateWeapon data, 
        float damage,
        float critChance,
        float critMultiplier,
        DamageType type,
        float speed,
        WeaponType Wtype);
    static void SlowSword(GameEngine::Scene& scene, CreateWeapon data);
    static void FastSword(GameEngine::Scene& scene, CreateWeapon data);
};
} // namespace Roguelike