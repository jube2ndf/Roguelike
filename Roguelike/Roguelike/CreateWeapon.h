#pragma once
#include "WeaponType.h"
#include <GameObject.h>
#include "SpawnEvent.h"
namespace Roguelike
{
struct CreateWeapon
{
    WeaponType type;
    SpawnProjectileEvent data;
    GameEngine::GameObject* source;
};
}